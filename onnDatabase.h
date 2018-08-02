#ifndef ONNDATABASE_H
#define ONNDATABASE_H

#include <QObject>
#include "onnObject.h"

class onnDatabase : public onnObject
{
    Q_OBJECT
public:
    explicit onnDatabase();

signals:

public slots:
    void onStart();
};

#endif // ONNDATABASE_H
