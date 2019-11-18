#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "neutron.h"
#include "manager.h"
#include <QVector>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new Manager(20, 200, 50, 50, 200, 100))
{
    QVector<int> neutron_count = {0};
    update_network(neutron_count);
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
    manager->draw(painter, active_brush, debug_brush, normal_brush, line_pen);
}

void MainWindow::mousePressEvent(QMouseEvent* me)
{
    manager->OnPress(me->x(), me->y());
    manager->OnRelease(me->x(), me->y());
    update_weight();
    update_activation();
    this->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent* me)
{
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

void MainWindow::update_network(QVector<int> network)
{
    manager->set_network(network.size(), network);
    manager->create();
}

void MainWindow::on_layer_count_edit_textChanged(const QString &arg1)
{
    int count = arg1.toInt();
    if (network_line_edit_vector.size() != 0)
    {
        network_line_edit_vector.clear();
    }
    for (int i = 0; i < count; i++)
    {
       network_line_edit_vector.append(shared_ptr<QLineEdit>(new QLineEdit(this)));
    }
    for (auto& iter : network_line_edit_vector)
    {
        ui->network_layout->addWidget(iter.get());
    }
}

void MainWindow::on_button_draw_clicked()
{
    QVector<int> neutron_network;
    neutron_network.clear();
    for (auto& iter : network_line_edit_vector)
    {
        neutron_network.append(iter->text().toInt());
    }
    update_network(neutron_network);
    this->update();
}

void MainWindow::on_button_random_clicked()
{
    manager->random_para();
    this->update();
}

void MainWindow::update_weight()
{
    shared_ptr<Neutron> n = manager->search_active();
    if (n == nullptr)
    {
        return;
    }
    QVector<double> para = n->get_weight_vector();
    weight_line_edit_vector.clear();
    for (int i = 0; i < para.size(); i++)
    {
        shared_ptr<QLineEdit> temp(new QLineEdit(this));
        temp->setText(QString::number(para[i]));
        weight_line_edit_vector.append(temp);
    }
    for (int i = 0; i < weight_line_edit_vector.size(); i++)
    {
        ui->para_layout->addWidget(weight_line_edit_vector[i].get());
    }
}

void MainWindow::on_button_update_clicked()
{
    shared_ptr<Neutron> neu(manager->search_active());
    QVector<double> para;
    for (auto& iter : weight_line_edit_vector)
    {
        para.append(iter->text().toDouble());
    }
    neu->update_para(para);
    int n = button_group.checkedId();
    if (n == -1)
    {

    }
    else if (n == ActivationFunction::ReLU)
    {
        neu->update_activation(shared_ptr<ActivationFunction>(new ActivationReLu));
    }
    else if (n == ActivationFunction::Sigmoid)
    {
        neu->update_activation(shared_ptr<ActivationFunction>(new ActivationSigmoid));
    }
    else if (n == ActivationFunction::Tanh)
    {
        neu->update_activation(shared_ptr<ActivationFunction>(new ActivationTanh));
    }
    else
    {
        throw "fault in activation selecting";
    }
    this->update();
}

void MainWindow::update_activation()
{
    shared_ptr<Neutron> neu(manager->search_active());
    if (neu == nullptr) return;
    if (neu->get_type() == Neutron::Input) return;
    shared_ptr<ActivationFunction> af = neu->get_activation();
    activation_radio_button_map.clear();
    activation_radio_button_map.insert(ActivationFunction::ReLU, shared_ptr<QRadioButton>(new QRadioButton("ReLU", this)));
    activation_radio_button_map.insert(ActivationFunction::Sigmoid, shared_ptr<QRadioButton>(new QRadioButton("Sigmoid", this)));
    activation_radio_button_map.insert(ActivationFunction::Tanh, shared_ptr<QRadioButton>(new QRadioButton("Tanh", this)));
    if (af)
    {
        activation_radio_button_map.find(af->get_type()).value()->setChecked(true);
    }
    ui->activation_layout->addWidget((*activation_radio_button_map.find(ActivationFunction::ReLU)).get());
    ui->activation_layout->addWidget((*activation_radio_button_map.find(ActivationFunction::Sigmoid)).get());
    ui->activation_layout->addWidget((*activation_radio_button_map.find(ActivationFunction::Tanh)).get());
    create_btn_group();
}

void MainWindow::create_btn_group()
{
    button_group.removeButton(activation_radio_button_map.find(ActivationFunction::ReLU)->get());
    button_group.removeButton(activation_radio_button_map.find(ActivationFunction::Sigmoid)->get());
    button_group.removeButton(activation_radio_button_map.find(ActivationFunction::Tanh)->get());

    button_group.addButton(activation_radio_button_map.find(ActivationFunction::ReLU)->get(), ActivationFunction::ReLU);
    button_group.addButton(activation_radio_button_map.find(ActivationFunction::Sigmoid)->get(), ActivationFunction::Sigmoid);
    button_group.addButton(activation_radio_button_map.find(ActivationFunction::Tanh)->get(), ActivationFunction::Tanh);
}
