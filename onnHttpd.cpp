#include "onnHttpd.h"
//#include <handy/handy.h>

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>

#include <evpp/http/http_server.h>

#define ISspace(x) isspace((int)(x))

#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"
#define STDIN   0
#define STDOUT  1
#define STDERR  2

extern onnHttpd        *blockHttpd;

onnHttpd::onnHttpd():onnObject("onnHttpd"){
    port = 3000;
}

void onnHttpd::runBlockNew(QByteArray pData){
    onBlockNew(pData);
}

//void onnHttpd::runHttpd(int pPort){
//    int threads = QThread::idealThreadCount()*2+1;
//    handy::setloglevel("FATAL");
//    handy::MultiBase base(threads);
//    handy::HttpServer httpd(&base);
//    int curPort = pPort;
//    while(!httpd.bind("", curPort)){
//        cout<<"runHttp failed:"<<curPort<<endl;
//        QThread::sleep(1);
//    }
//    cout<<"runHttp ok:"<<curPort<<endl;
//    httpd.onDefault([&](const handy::HttpConnPtr& con){
//        string v = con.getRequest().version;
//        handy::HttpResponse resp;
//        QByteArray msg;
//        if(con.getRequest().method == "GET"){
//            msg = (con.getRequest().query_uri.c_str());
//            con.clearData();
//            QByteArray result = doHandlerGet(msg);
//            if(!result.isEmpty()){
//                resp.body = handy::Slice(result.data(),result.count());
//            }else{
//                resp.body = handy::Slice("null");
//            }
//        }else if(con.getRequest().method == "POST"){
//            msg = (con.getRequest().body.c_str());
//            con.clearData();
//            resp.body = handy::Slice(GETSHA256(msg));
//            //emit doBlockNew(msg);
//            QtConcurrent::run(QThreadPool::globalInstance(),this,&onnHttpd::runBlockNew,msg);
//        }else{
//            con.clearData();
//            resp.body = handy::Slice(GETSHA256(msg));
//            cout << "httpd unknow method" << con.getRequest().method << endl;
//        }
//        con.sendResponse(resp);
//        if (v == "HTTP/1.0") {
//            con->close();
//        }
//    });
//    handy::Signal::signal(SIGINT, [&]{base.exit();});
//    base.loop();
//}

/**********************************************************************/
/* A request has caused a call to accept() on the server port to
 * return.  Process the request appropriately.
 * Parameters: the socket connected to the client */
/**********************************************************************/

void rsp(int fd,QString data){
    data.push_front("HTTP/1.1 200 OK\r\n\r\n");
    send(fd,data.toLatin1().data(),data.count(),0);
}

void onnHttpd::accept_request(int arg)
{
    int nNetTimeout=1;//10秒，
    //设置发送超时
    setsockopt(arg,SOL_SOCKET,SO_SNDTIMEO,(char *)&nNetTimeout,sizeof(int));
    //设置接收超时
    setsockopt(arg,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));
    int client = arg;
    char buf[20000] = {0};
    QThread::usleep(500);
    ssize_t numchars = recv(client,buf,20000,0);
    if(numchars <= 0){
        QThread::usleep(500);
        recv(client,buf,20000,0);
    }
    QString curBuf = buf;
    QStringList curList = QString(buf).split("\r\n");
    if(curList.isEmpty() || numchars <= 0){
        rsp(client,"curList.isEmpty()");
        shutdown(client,SHUT_RDWR);
        return;
    }
    QByteArray msg;
    QByteArray result;
    if(curBuf.left(3) == "GET"){
        QStringList curData = curList.first().split(" ");
        if(curData.count()<2){
            rsp(client,"curData.count()<2");
            shutdown(client,SHUT_RDWR);
            return;
        }
        msg = curData.at(1).toLatin1();
        result = doHandlerGet(msg);
        if(result.isEmpty()){
            result = "null";
        }
    }else if(curBuf.left(4) == "POST"){
        msg = curList.last().toLatin1();
        result = GETSHA256(msg);
        emit doBlockNew(msg);
        //QtConcurrent::run(this,&onnHttpd::runBlockNew,msg);
    }else{
        msg = buf;
        result = GETSHA256(msg);
        BUG << "httpd unknow method" << curList;
    }
    rsp(client,result);
    shutdown(client,SHUT_RDWR);
}

/**********************************************************************/
/* Inform the client that a request it has made has a problem.
 * Parameters: client socket */
/**********************************************************************/
void onnHttpd::bad_request(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "<P>Your browser sent a bad request, ");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "such as a POST without a Content-Length.\r\n");
    send(client, buf, sizeof(buf), 0);
}

/**********************************************************************/
/* Put the entire contents of a file out on a socket.  This function
 * is named after the UNIX "cat" command, because it might have been
 * easier just to do something like pipe, fork, and exec("cat").
 * Parameters: the client socket descriptor
 *             FILE pointer for the file to cat */
/**********************************************************************/
void onnHttpd::cat(int client, FILE *resource)
{
    char buf[1024];

    fgets(buf, sizeof(buf), resource);
    while (!feof(resource))
    {
        send(client, buf, strlen(buf), 0);
        fgets(buf, sizeof(buf), resource);
    }
}

/**********************************************************************/
/* Inform the client that a CGI script could not be executed.
 * Parameter: the client socket descriptor. */
/**********************************************************************/
void onnHttpd::cannot_execute(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 500 Internal Server Error\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<P>Error prohibited CGI execution.\r\n");
    send(client, buf, strlen(buf), 0);
}

/**********************************************************************/
/* Print out an error message with perror() (for system errors; based
 * on value of errno, which indicates system call errors) and exit the
 * program indicating an error. */
/**********************************************************************/
void onnHttpd::error_die(const char *sc)
{
    perror(sc);
    exit(1);
}

/**********************************************************************/
/* Execute a CGI script.  Will need to set environment variables as
 * appropriate.
 * Parameters: client socket descriptor
 *             path to the CGI script */
/**********************************************************************/
void onnHttpd::execute_cgi(int client, const char *path,
        const char *method, const char *query_string)
{
    char buf[1024];
    int cgi_output[2];
    int cgi_input[2];
    pid_t pid;
    int status;
    int i;
    char c;
    int numchars = 1;
    int content_length = -1;

    buf[0] = 'A'; buf[1] = '\0';
    if (strcasecmp(method, "GET") == 0)
        while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
            numchars = get_line(client, buf, sizeof(buf));
    else if (strcasecmp(method, "POST") == 0) /*POST*/
    {
        numchars = get_line(client, buf, sizeof(buf));
        while ((numchars > 0) && strcmp("\n", buf))
        {
            buf[15] = '\0';
            if (strcasecmp(buf, "Content-Length:") == 0)
                content_length = atoi(&(buf[16]));
            numchars = get_line(client, buf, sizeof(buf));
        }
        if (content_length == -1) {
            bad_request(client);
            return;
        }
    }
    else/*HEAD or other*/
    {
    }


    if (pipe(cgi_output) < 0) {
        cannot_execute(client);
        return;
    }
    if (pipe(cgi_input) < 0) {
        cannot_execute(client);
        return;
    }

    if ( (pid = fork()) < 0 ) {
        cannot_execute(client);
        return;
    }
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    send(client, buf, strlen(buf), 0);
    if (pid == 0)  /* child: CGI script */
    {
        char meth_env[255];
        char query_env[255];
        char length_env[255];

        dup2(cgi_output[1], STDOUT);
        dup2(cgi_input[0], STDIN);
        close(cgi_output[0]);
        close(cgi_input[1]);
        sprintf(meth_env, "REQUEST_METHOD=%s", method);
        putenv(meth_env);
        if (strcasecmp(method, "GET") == 0) {
            sprintf(query_env, "QUERY_STRING=%s", query_string);
            putenv(query_env);
        }
        else {   /* POST */
            sprintf(length_env, "CONTENT_LENGTH=%d", content_length);
            putenv(length_env);
        }
        execl(path, NULL);
        exit(0);
    } else {    /* parent */
        close(cgi_output[1]);
        close(cgi_input[0]);
        if (strcasecmp(method, "POST") == 0)
            for (i = 0; i < content_length; i++) {
                recv(client, &c, 1, 0);
                write(cgi_input[1], &c, 1);
            }
        while (read(cgi_output[0], &c, 1) > 0)
            send(client, &c, 1, 0);

        close(cgi_output[0]);
        close(cgi_input[1]);
        waitpid(pid, &status, 0);
    }
}

/**********************************************************************/
/* Get a line from a socket, whether the line ends in a newline,
 * carriage return, or a CRLF combination.  Terminates the string read
 * with a null character.  If no newline indicator is found before the
 * end of the buffer, the string is terminated with a null.  If any of
 * the above three line terminators is read, the last character of the
 * string will be a linefeed and the string will be terminated with a
 * null character.
 * Parameters: the socket descriptor
 *             the buffer to save the data in
 *             the size of the buffer
 * Returns: the number of bytes stored (excluding null) */
/**********************************************************************/
int onnHttpd::get_line(int sock, char *buf, int size)
{
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n'))
    {
        n = recv(sock, &c, 1, 0);
        /* DEBUG printf("%02X\n", c); */
        if (n > 0)
        {
            if (c == '\r')
            {
                n = recv(sock, &c, 1, MSG_PEEK);
                /* DEBUG printf("%02X\n", c); */
                if ((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
            buf[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buf[i] = '\0';

    return(i);
}

/**********************************************************************/
/* Return the informational HTTP headers about a file. */
/* Parameters: the socket to print the headers on
 *             the name of the file */
/**********************************************************************/
void onnHttpd::headers(int client, const char *filename)
{
    char buf[1024];
    (void)filename;  /* could use filename to determine file type */

    strcpy(buf, "HTTP/1.0 200 OK\r\n");
    send(client, buf, strlen(buf), 0);
    strcpy(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    strcpy(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
}

/**********************************************************************/
/* Give a client a 404 not found status message. */
/**********************************************************************/
void onnHttpd::not_found(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "your request because the resource specified\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "is unavailable or nonexistent.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

/**********************************************************************/
/* Send a regular file to the client.  Use headers, and report
 * errors to client if they occur.
 * Parameters: a pointer to a file structure produced from the socket
 *              file descriptor
 *             the name of the file to serve */
/**********************************************************************/
void onnHttpd::serve_file(int client, const char *filename)
{
    FILE *resource = NULL;
    int numchars = 1;
    char buf[1024];

    buf[0] = 'A'; buf[1] = '\0';
    while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
        numchars = get_line(client, buf, sizeof(buf));

    resource = fopen(filename, "r");
    if (resource == NULL)
        not_found(client);
    else
    {
        headers(client, filename);
        cat(client, resource);
    }
    fclose(resource);
}

/**********************************************************************/
/* This function starts the process of listening for web connections
 * on a specified port.  If the port is 0, then dynamically allocate a
 * port and modify the original port variable to reflect the actual
 * port.
 * Parameters: pointer to variable containing the port to connect on
 * Returns: the socket */
/**********************************************************************/
int onnHttpd::startup(u_short *port)
{
    int httpd = 0;
    int on = 1;
    struct sockaddr_in name;

    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        error_die("socket");
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
    {
        error_die("setsockopt failed");
    }
    if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
        error_die("bind");
    if (*port == 0)  /* if dynamically allocating a port */
    {
        socklen_t namelen = sizeof(name);
        if (getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
            error_die("getsockname");
        *port = ntohs(name.sin_port);
    }
    if (listen(httpd, 5) < 0)
        error_die("listen");
    return(httpd);
}

/**********************************************************************/
/* Inform the client that the requested web method has not been
 * implemented.
 * Parameter: the client socket */
/**********************************************************************/
void onnHttpd::unimplemented(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</TITLE></HEAD>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

/**********************************************************************/

void onnHttpd::runHttpdold(int pPort)
{
    int server_sock = -1;
    u_short port = pPort;
    int client_sock = -1;
    struct sockaddr_in client_name;
    socklen_t  client_name_len = sizeof(client_name);
    //pthread_t newthread;

    server_sock = startup(&port);
    printf("httpd running on port %d\n", port);

    while (1)
    {
        client_sock = accept(server_sock,(struct sockaddr *)&client_name,&client_name_len);
        if (client_sock == -1){
            continue;
        }
        /* accept_request(&client_sock); */
        //if (pthread_create(&newthread , NULL, (void *)accept_request, (void *)(intptr_t)client_sock) != 0)
        //    perror("pthread_create");
        //QtConcurrent::run(QThreadPool::globalInstance(),this,&onnHttpd::runBlockNew,msg);
        //QtConcurrent::run(this,&onnHttpd::accept_request,client_sock);
        accept_request(client_sock);
    }
    close(server_sock);
}

void onnHttpd::runHttpd(int pPort) {
    std::vector<int> ports = { 9009, 23456, 23457 };
    int port = pPort;
    int thread_num = 2;

    ports.push_back(port);

    evpp::http::Server server(thread_num);
    server.SetThreadDispatchPolicy(evpp::ThreadDispatchPolicy::kIPAddressHashing);
    server.RegisterDefaultHandler([&](evpp::EventLoop* loop,const evpp::http::ContextPtr& ctx,const evpp::http::HTTPSendResponseCallback& cb) {
        std::stringstream oss;
        QByteArray msg = ctx->uri().c_str();
        QByteArray result;
        if(ctx->body().ToString().size()>0){//POST
            result = GETSHA256(msg);
            //emit doBlockNew(msg);
            QtConcurrent::run(this,&onnHttpd::runBlockNew,msg);
        }else{//GET
            result = doHandlerGet(msg);
            if(result.isEmpty()){
                result = "null";
            }
        }
        oss << result.toStdString();
        cb(oss.str());
    });
//    server.RegisterHandler("/echo",[&](evpp::EventLoop* loop,const evpp::http::ContextPtr& ctx,const evpp::http::HTTPSendResponseCallback& cb) {
//        cb(ctx->body().ToString());
//    });
    server.Init(ports);
    server.Start();
    while (!server.IsStopped()) {
        usleep(1);
    }
}

void onnHttpd::onStart(){
    if(flagStart){
        return;
    }
    onnObject *senderObj = qobject_cast<onnObject *>(sender());
    flagStart = true;
    emit doStartFinish();
    if(!getArgument("-p").isEmpty()){
        std::cout << "httpd start:" << senderObj->objectName().toStdString() << " " << senderObj->objType.toStdString() <<std::endl;
        //runHttpd(getArgument("-p").toInt());
        QtConcurrent::run(this,&onnHttpd::runHttpd,getArgument("-p").toInt());
    }else{
        std::cout << "httpd stop" << senderObj->objectName().toStdString() << " " << senderObj->objType.toStdString() <<std::endl;
    }
}
