#include "tasksource.h"
#include <QTimer>

TaskSource::TaskSource(QObject *parent, std::string name, int priority, std::shared_ptr<Buffer> buf) {
    count_ = 0;
    name_ = name;
    priority_ = priority;
    buffer_ = buf;
}

void TaskSource::taskManager(std::string name, int executionTime, int startTime) {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() { generateTask(name, executionTime); });
    timer->setSingleShot(true);
    timer->start(startTime*100);
}

void TaskSource::generateTask(std::string name, int executionTime) {
    buffer_->addTaskToBuffer(std::make_unique<Task>(name, this, executionTime));
}

int TaskSource::getPriority() {
    return priority_;
}

std::string TaskSource::getName() {
    return name_;
}
