#ifndef ONNUDPD_H
#define ONNUDPD_H

#include <QObject>
#include "onnObject.h"

class onnUdpd : public onnObject
{
    Q_OBJECT
public:
    explicit onnUdpd();

signals:

public slots:
    void onStart();
};

#endif // ONNUDPD_H
