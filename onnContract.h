#ifndef ONNCONTRACT_H
#define ONNCONTRACT_H

#include <QObject>
#include "onnObject.h"

class onnContract : public onnObject
{
    Q_OBJECT
public:
    explicit onnContract();
    QString timeoutContract;
    QString timeoutResult;
signals:
    void timerStop();
public slots:
    void onStart();
    void onTimeout();
};

#endif // ONNCONTRACT_H
