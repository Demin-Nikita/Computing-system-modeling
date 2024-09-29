#ifndef TASKSOURCE_H
#define TASKSOURCE_H

#include <String>
#include <memory>
#include <QObject>
#include <QThread>
#include "buffer.h"

class  Task;

class TaskSource : public QObject {
    Q_OBJECT

private:
    int count_;
    int priority_;
    std::string name_;
    std::shared_ptr<Buffer> buffer_;

public:
    TaskSource(QObject *parent, std::string name, int priority, std::shared_ptr<Buffer> buf);

    int getPriority();
    std::string getName();
    void taskManager(std::string name, int executionTime, int startTime);
public slots:
    void generateTask(std::string name, int executionTime);
};

#endif // TASKSOURCE_H
