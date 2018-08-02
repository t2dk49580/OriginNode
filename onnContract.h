#ifndef ONNCONTRACT_H
#define ONNCONTRACT_H

#include <QObject>
#include "onnObject.h"

class onnContract : public onnObject
{
    Q_OBJECT
public:
    explicit onnContract();

signals:

public slots:
    void onStart();
};

#endif // ONNCONTRACT_H
