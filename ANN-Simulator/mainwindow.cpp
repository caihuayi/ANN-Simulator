#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "neutron.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPen pen(Qt::red);
    QBrush brush(Qt::red, Qt::BrushStyle::Dense6Pattern);
    test_painter.reset(new QPainter(this));
    test_painter->setPen(pen);
    test_painter->setBrush(brush);
    ui->setupUi(this);
    QPoint point(20, 20);
    n.reset(new Neutron(point, 100, 100));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPen pen(Qt::red);
    QBrush brush(Qt::red, Qt::BrushStyle::Dense6Pattern);
    shared_ptr<QPainter> test_painter(new QPainter(this));
    test_painter->setPen(pen);
    test_painter->setBrush(brush);
    n->draw(test_painter, test_painter, test_painter);
}
void MainWindow::mousePressEvent(QMouseEvent* me)
{

}

void MainWindow::mouseMoveEvent(QMouseEvent* me)
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent* me)
{

}
