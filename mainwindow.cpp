#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videoCapture.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cap = new VideoCapture(this);

    isClicked = true;

    connect(cap, &VideoCapture::newPixmapCaptured, this, [&]()
            { ui->camLabel->setPixmap(cap->pixmap().scaled(500, 500)); });
    connect(ui->activeButton, &QPushButton::clicked, this, &MainWindow::activeButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    cap->terminate();
}

void MainWindow::activeButtonClicked()
{
    if (isClicked == true)
    {
        ui->activeButton->setText("Turn off");
        cap->start(QThread::HighestPriority);
        isClicked = false;
    }
    else
    {
        ui->activeButton->setText("Activate");
        cap->terminate();
        isClicked = true;
    }
}