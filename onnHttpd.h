#ifndef ONNHTTPD_H
#define ONNHTTPD_H

#include <QObject>
#include "onnObject.h"

class onnHttpd : public onnObject
{
    Q_OBJECT
public:
    explicit onnHttpd();
    void runBlockNew(QByteArray);
    void runHttpd(int);

    void runHttpdold(int);
    void accept_request(int);
    void bad_request(int);
    void cat(int, FILE *);
    void cannot_execute(int);
    void error_die(const char *);
    void execute_cgi(int, const char *, const char *, const char *);
    int get_line(int, char *, int);
    void headers(int, const char *);
    void not_found(int);
    void serve_file(int, const char *);
    int startup(u_short *);
    void unimplemented(int);

signals:

public slots:
    void onStart();
private:
    QStringList mMethod;
    int port;
    QTcpServer *mServer;
};

#endif // ONNHTTPD_H
