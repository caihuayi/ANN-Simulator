#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "neutron.h"
#include "manager.h"

#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new Manager(20, 20, 50, 50, 100, 100))
{
    /********test single neutron***********/
   /* QPen pen(Qt::red);
    QBrush brush(Qt::red, Qt::BrushStyle::Dense6Pattern);
    test_painter.reset(new QPainter(this));
    test_painter->setPen(pen);
    test_painter->setBrush(brush);
    QPoint point(20, 20);
    n.reset(new Neutron(point, 100, 100));*/
     /*******test all***************/
    manager->create(5);
     /****************************/
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_painter(std::shared_ptr<QPainter> active_painter
                  , std::shared_ptr<QPainter> debug_painter
                  , std::shared_ptr<QPainter> normal_painter)
{
    shared_ptr<QPen> active_pen(new QPen(Qt::red));
    shared_ptr<QBrush> active_brush(new QBrush(Qt::red, Qt::BrushStyle::Dense6Pattern));
    active_painter.reset(new QPainter());
    active_painter->setPen(*active_pen);
    active_painter->setBrush(*active_brush);

    shared_ptr<QPen> debug_pen(new QPen(Qt::green));
    shared_ptr<QBrush> debug_brush(new QBrush(Qt::green, Qt::BrushStyle::Dense6Pattern));
    debug_painter.reset(new QPainter());
    debug_painter->setPen(*debug_pen);
    debug_painter->setBrush(*debug_brush);

    shared_ptr<QPen> normal_pen(new QPen(Qt::black));
    shared_ptr<QBrush> normal_brush(new QBrush(Qt::BrushStyle::NoBrush));
    normal_painter.reset(new QPainter());
    normal_painter->setPen(*normal_pen);
    normal_painter->setBrush(*normal_brush);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    /*
    QPen pen(Qt::red);
    QBrush brush(Qt::red, Qt::BrushStyle::Dense6Pattern);
    shared_ptr<QPainter> test_painter(new QPainter(this));
    test_painter->setPen(pen);
    test_painter->setBrush(brush);*/
    shared_ptr<QPainter> painter;

    shared_ptr<QPen> active_pen(new QPen(Qt::red));
    shared_ptr<QBrush> active_brush(new QBrush(Qt::red, Qt::BrushStyle::Dense6Pattern));


    shared_ptr<QPen> debug_pen(new QPen(Qt::green));
    shared_ptr<QBrush> debug_brush(new QBrush(Qt::green, Qt::BrushStyle::Dense6Pattern));

    shared_ptr<QPen> normal_pen(new QPen(Qt::black));
    shared_ptr<QBrush> normal_brush(new QBrush(Qt::white, Qt::BrushStyle::SolidPattern));

    shared_ptr<QPen> line_pen(new QPen(Qt::black));
    line_pen->setStyle(Qt::PenStyle::DotLine);

    painter.reset(new QPainter(this));
    painter->setPen(*normal_pen);
    painter->setBrush(*active_brush);
    cout << "print event" << endl;
    manager->draw(painter, active_brush, debug_brush, normal_brush, line_pen);
}

void MainWindow::mousePressEvent(QMouseEvent* me)
{
    /*
    n->OnRelease(me->x(), me->y());
    */
    manager->OnPress(me->x(), me->y());
    manager->OnRelease(me->x(), me->y());

    this->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent* me)
{
    /*
    n->OnPress(me->x(), me->y());
    n->OnMove(me->x()-n->get_old_point().x(), me->y()-n->get_old_point().y());
    this->update();
    n->OnRelease(me->x(), me->y());
    */
    shared_ptr<Neutron> n = manager->search_active();
    if (n != nullptr)
    {
        n->OnPress(me->x(), me->y());
        manager->update_fbpoint();
        n->OnMove(me->x()-n->get_old_point().x(), me->y()-n->get_old_point().y());
        this->update();
        n->OnRelease(me->x(), me->y());
    }

    this->update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* me)
{

}
