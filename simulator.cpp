#include "simulator.h"
#include "buffer.h"
#include "tasksource.h"
#include "computingunit.h"
#include "task.h"
#include <QDebug>
#include <QObject>
#include <QTableWidget>

Simulator::Simulator() {
    QObject *parent = new QObject();
    buffer = std::make_shared<Buffer>(4);

    sources.push_back(std::make_shared<TaskSource>(parent, "Military", 3, buffer));
    sources.push_back(std::make_shared<TaskSource>(parent, "Science", 2, buffer));
    sources.push_back(std::make_shared<TaskSource>(parent, "Other research", 1, buffer));

    for (int i = 0; i < 3; i++) {
        units.push_back(std::make_shared<ComputingUnit>(parent, buffer, i));
    }
}

void Simulator::readTasks(QTableWidget* tableWidget) {
    std::string name;

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        auto item = tableWidget->item(row, 0);
        if (item == nullptr) { continue; } else { name = item->text().toStdString(); }
        int id = tableWidget->item(row, 1)->text().toInt();
        int startTime = tableWidget->item(row, 2)->text().toInt();
        int executionTime = tableWidget->item(row, 3)->text().toInt();

        sources[id]->taskManager(name, executionTime, startTime);
    }
}

void Simulator::start() {
    for (int i = 0; i < 3; i++) {
        units[i]->start();
    }
}
