#ifndef BUFFER_H
#define BUFFER_H

#include <list>
#include <memory>
#include "task.h"

using TaskPtr = std::unique_ptr<Task>;
using TaskList = std::list<TaskPtr>;

class Buffer
{
private:
    int numOfSlots_;
    int TasksInBuffer_;
    std::unique_ptr<TaskList> memory_;
public:
    Buffer(int numOfSlots);
    void addTaskToBuffer(TaskPtr t);
    std::unique_ptr<Task> getTask();
};

#endif // BUFFER_H
