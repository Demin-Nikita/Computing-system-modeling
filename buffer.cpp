#include "buffer.h"
#include "tasksource.h"
#include <QDebug>

Buffer::Buffer(int numOfSlots) {
    numOfSlots_ = numOfSlots;
    TasksInBuffer_ = 0;
    memory_ = std::make_unique<TaskList>();
}

void Buffer::addTaskToBuffer(TaskPtr t) {

    if (TasksInBuffer_ < numOfSlots_) {
        memory_->push_back(std::move(t));
    }
    else {
        int mnPriority = 0;
        int curPriority = 0;
        auto forDel = memory_->begin();
        for (auto it = memory_->begin(); it != memory_->end(); it++) {
            curPriority = (*it)->getSource()->getPriority();
            if (curPriority < mnPriority) {
                mnPriority = curPriority;
                forDel = it;
            }
        }
        memory_->erase(forDel);
        memory_->push_back(std::move(t));
    }
}

std::unique_ptr<Task> Buffer::getTask() {
    int mxPriority = 0;
    int curPriority = 0;
    auto forExec = memory_->begin();
    for (auto it = memory_->begin(); it != memory_->end(); it++) {
        curPriority = (*it)->getSource()->getPriority();
        if (curPriority > mxPriority) {
            mxPriority = curPriority;
            forExec = it;
        }
    }

    std::unique_ptr<Task> nextTask;
    if (*forExec == nullptr) {
        nextTask = nullptr;
    } else {
        nextTask = std::move(*forExec);
        memory_->erase(forExec);
    }
    return nextTask;
}
