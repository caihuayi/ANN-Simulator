#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "neutron.h"
#include "manager.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new Manager(20, 20, 50, 50, 100, 100))
{
    /********test single neutron***********/
    QPen pen(Qt::red);
    QBrush brush(Qt::red, Qt::BrushStyle::Dense6Pattern);
    test_painter.reset(new QPainter(this));
    test_painter->setPen(pen);
    test_painter->setBrush(brush);
    QPoint point(20, 20);
    n.reset(new Neutron(point, 100, 100));
     /*******test all***************/
    manager->create(5);
     /****************************/
    ui->setupUi(this);
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
    manager->draw(test_painter, test_painter, test_painter);
}
void MainWindow::mousePressEvent(QMouseEvent* me)
{
    /*
    n->OnRelease(me->x(), me->y());
    */


}

void MainWindow::mouseMoveEvent(QMouseEvent* me)
{
    /*
    n->OnPress(me->x(), me->y());
    n->OnMove(me->x()-n->get_old_point().x(), me->y()-n->get_old_point().y());
    this->update();
    n->OnRelease(me->x(), me->y());
    */

}

void MainWindow::mouseReleaseEvent(QMouseEvent* me)
{

}
