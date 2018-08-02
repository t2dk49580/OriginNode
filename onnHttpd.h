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

signals:

public slots:
    void onStart();
};

#endif // ONNHTTPD_H
