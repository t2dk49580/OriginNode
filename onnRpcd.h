#ifndef ONNRPCD_H
#define ONNRPCD_H

#include <QObject>
#include "onnObject.h"

class onnRpcd : public onnObject
{
    Q_OBJECT
public:
    explicit onnRpcd();
    void runRpcd(int);
signals:

public slots:
    void onStart();
};

#endif // ONNRPCD_H
