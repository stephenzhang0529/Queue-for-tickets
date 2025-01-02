#ifndef TICKETSALE_H
#define TICKETSALE_H

#include <QMainWindow>
#include"fun.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class TicketSale;
}
QT_END_NAMESPACE

class TicketSale : public QMainWindow
{
    Q_OBJECT

public:
    TicketSale(QWidget *parent = nullptr);
    ~TicketSale();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TicketSale *ui;
    fun a;
};
#endif // TICKETSALE_H
