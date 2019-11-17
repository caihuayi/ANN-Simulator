#ifndef DIALOGSETNETWORK_H
#define DIALOGSETNETWORK_H

#include <QDialog>
#include <QVector>
#include <QLineEdit>
#include <memory>
#include "mainwindow.h"

namespace Ui {
class DialogSetNetwork;
}

class DialogSetNetwork : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetNetwork(QWidget *parent = nullptr);
    QVector<int> get_network() const;
    void set_callback(void (*f)(QVector<int>));
    ~DialogSetNetwork();

private slots:
    void on_layer_count_edit_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::DialogSetNetwork *ui;
    QVector<std::shared_ptr<QLineEdit>> line_edit_vector;
    void (*callback)(QVector<int>);
};

#endif // DIALOGSETNETWORK_H
