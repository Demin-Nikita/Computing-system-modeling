#ifndef COMPUTINGUNIT_H
#define COMPUTINGUNIT_H

#include "task.h"
#include "buffer.h"
#include <memory>
#include <QThread>
#include <QTimer>

class ComputingUnit : public QThread {
    Q_OBJECT

public:
    ComputingUnit(QObject *parent, std::shared_ptr<Buffer> buf, int name);
    ~ComputingUnit();
    bool ready() const;
    void setTask(std::unique_ptr<Task> t);

protected:
    void run() override;

private slots:
    void getNewTask();
    void ExecTask();

private:
    std::shared_ptr<Buffer> buf_;
    std::shared_ptr<Task> task_;
    int name_;
};
#endif // COMPUTINGUNIT_H
