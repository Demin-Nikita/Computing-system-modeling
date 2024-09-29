// #include "mainwindow.h"
// #include "./ui_mainwindow.h"

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);
// }

// MainWindow::~MainWindow()
// {
//     delete ui;
// }

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
    , elapsedTimer(new QElapsedTimer())
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateProgress);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateElapsedTime);

    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete elapsedTimer;
}

void MainWindow::updateProgress()
{
    //s.update();
    ui->firstUnitProgressBar->setValue(10);
    ui->secondUnitProgressBar->setValue(20);
    ui->thirdUnitProgressBar->setValue(30);
    ui->fourthUnitProgressBar->setValue(40);
}

void MainWindow::updateElapsedTime()
{
    QString elapsedTime = QString("00:00:000");

    if (simulation) {
        qint64 elapsedSeconds = elapsedTimer->elapsed();
        updateProgress();

        elapsedTime = QString("%1:%2:%3")
                                  .arg(elapsedSeconds / 1000 % 3600 / 60, 2, 10, QChar('0'))
                                  .arg((elapsedSeconds / 1000) % 60, 2, 10, QChar('0'))
                                  .arg(elapsedSeconds % 1000, 2, 10, QChar('0'));
    }

    ui->timeLabel->setText(elapsedTime);
}

void MainWindow::on_TaskConfirmButton_clicked()
{
    s.readTasks(ui->tableWidget);
    s.start();
    simulation = true;
    elapsedTimer->start();
}

