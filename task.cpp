#include "task.h"
#include <iostream>

Task::Task(std::string name, TaskSource* source, int executionTime) {
    name_ = name;
    source_ = source;
    executionTime_ = executionTime;
}

TaskSource* Task::getSource() {
    return source_;
}

std::string Task::getName() {
    return name_;
}

void Task::execute() {
    std::cout << "Executing " << name_ << std::endl;
}
