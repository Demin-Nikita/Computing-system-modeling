#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "computingunit.h"
#include <QTableWidget>
#include <memory>

class Simulator
{
private:
    std::vector<std::shared_ptr<ComputingUnit>> units;
    std::shared_ptr<Buffer> buffer;
    std::vector<std::shared_ptr<TaskSource>> sources;

public:
    Simulator();
    void readTasks(QTableWidget* tableWidget);
    void start();
//    void update();
};

#endif // SIMULATOR_H
