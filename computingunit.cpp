#include "computingunit.h"
#include "tasksource.h"
#include <QDebug>
#include <QThread>


ComputingUnit::ComputingUnit(QObject *parent, std::shared_ptr<Buffer> buf, int name)
    : QThread(parent), buf_(buf), task_(nullptr), name_(name) {}

ComputingUnit::~ComputingUnit() {
    if (isRunning()) {
        quit();
        wait();
    }
}

void ComputingUnit::run() {
    QTimer taskTimer;

    connect(&taskTimer, &QTimer::timeout, this, &ComputingUnit::getNewTask);
    taskTimer.start(500);

    exec();
}

void ComputingUnit::getNewTask() {
    if (ready()) {
        task_ = buf_->getTask();
        ExecTask();
    }
}

void ComputingUnit::setTask(std::unique_ptr<Task> t) {
    task_ = std::move(t);
}

void ComputingUnit::ExecTask() {
    if (task_ != nullptr) {
        QTimer::singleShot(task_->getExecTime() * 100, this, [this]() {
            qDebug() << "Unit" << name_ << "finished task:" << task_->getName();
            task_ = nullptr;
        });
    }
}

bool ComputingUnit::ready() const {
    return task_ == nullptr;
}
