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

signals:

public slots:
    void onStart();
private:
    QStringList mMethod;
};

#endif // ONNHTTPD_H
