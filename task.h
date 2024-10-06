#ifndef TASK_H
#define TASK_H

#include <String>

class TaskSource;

class Task
{
private:
    std::string name_;
    int executionTime_;
    TaskSource* source_;
public:
    Task(std::string name, TaskSource* sourse, int executionTime);
    TaskSource* getSource();
    std::string getName();
    int getExecTime();
    void execute();
};

#endif // TASK_H
