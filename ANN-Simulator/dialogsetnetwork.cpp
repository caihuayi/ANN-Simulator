#include "dialogsetnetwork.h"
#include "ui_dialogsetnetwork.h"
#include <iostream>

using namespace std;

DialogSetNetwork::DialogSetNetwork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetNetwork)
{
    ui->setupUi(this);
}

DialogSetNetwork::~DialogSetNetwork()
{
    delete ui;
}

void DialogSetNetwork::on_layer_count_edit_textChanged(const QString &arg1)
{

    int count = arg1.toInt();
    if (line_edit_vector.size() != 0)
    {
        line_edit_vector.clear();
    }
    for (int i = 0; i < count; i++)
    {
        cout << "first for" << endl;
       line_edit_vector.append(shared_ptr<QLineEdit>(new QLineEdit(this)));
    }
    for (auto& iter : line_edit_vector)
    {
        cout << "second for" << endl;
        ui->network_layout->addWidget(iter.get());
    }

}

void DialogSetNetwork::on_buttonBox_accepted()
{

}

void DialogSetNetwork::set_callback(void (*f)(QVector<int>))
{
    callback = f;
}
