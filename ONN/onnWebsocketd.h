#ifndef ONNWEBSOCKETD_H
#define ONNWEBSOCKETD_H

#include <QObject>
#include "onnObject.h"

class onnWebsocketd : public onnObject
{
    Q_OBJECT
public:
    explicit onnWebsocketd();

    void runWebsocketd(int);
signals:

public slots:
    void onStart();
};

#endif // ONNWEBSOCKETD_H
