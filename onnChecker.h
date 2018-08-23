#ifndef ONNCHECKER_H
#define ONNCHECKER_H

#include <QObject>
#include "onnObject.h"

class onnChecker : public onnObject
{
    Q_OBJECT
public:
    explicit onnChecker();

signals:

public slots:
    void onStart();
};

#endif // ONNCHECKER_H
