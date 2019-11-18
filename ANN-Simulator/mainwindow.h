#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <memory>
#include <QLineEdit>
#include <QVector>
#include <QRadioButton>
#include <QMap>
#include <QButtonGroup>
#include "activationfunction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Neutron;
class Manager;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_layer_count_edit_textChanged(const QString &arg1);

    void on_button_draw_clicked();

    void on_button_random_clicked();

    void on_button_update_clicked();

    void on_button_compute_all_clicked();

    void on_button_debug_clicked();

private:
    Ui::MainWindow *ui;
    //test all
    std::shared_ptr<Manager> manager;
    //test end
    QVector<std::shared_ptr<QLineEdit>> network_line_edit_vector;
    QVector<std::shared_ptr<QLineEdit>> weight_line_edit_vector;
    QMap<ActivationFunction::ActivationType, std::shared_ptr<QRadioButton>> activation_radio_button_map;
    QButtonGroup button_group;

    void init_painter(std::shared_ptr<QPainter>, std::shared_ptr<QPainter>, std::shared_ptr<QPainter>);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void update_network(QVector<int> network);
    void update_weight();
    void update_activation();
    void create_btn_group();
};
#endif // MAINWINDOW_H
