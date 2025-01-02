#include "ticketsale.h"
#include "ui_ticketsale.h"
TicketSale::TicketSale(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicketSale)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget_3->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 85);
    ui->tableWidget->setColumnWidth(1, 85);
    ui->tableWidget_2->setColumnWidth(0, 85);
    ui->tableWidget_2->setColumnWidth(1, 85);
    ui->tableWidget_3->setColumnWidth(0, 85);
    ui->tableWidget_3->setColumnWidth(1, 85);
}

TicketSale::~TicketSale()
{
    delete ui;
}

void TicketSale::on_pushButton_clicked()
{
    QString num1=ui->lineEdit->text();
    ui->lineEdit->clear();
    bool ok;
    int num=num1.toInt(&ok);
    if(ok==false)
    {
        ui->lineEdit->setText("输入的为非数字类型！");
        return;
    }
    int row=0;
    ui->tableWidget_3->clear();
    ui->tableWidget_3->setRowCount(num);
    ui->tableWidget_3->setHorizontalHeaderLabels({"号码","类型"});

    for(int i=0;i<num;i++)
    {
        Fan fan=a.addfan();
        if(fan.level==-1)
        {
            ui->tableWidget_3->setItem(row,0,new QTableWidgetItem("队列"));
            ui->tableWidget_3->setItem(row,1,new QTableWidgetItem("已满！"));
            break;
        }
        ui->tableWidget_3->setItem(row,0,new QTableWidgetItem(QString::number(fan.number)));
        ui->tableWidget_3->setItem(row,1,new QTableWidgetItem(QString::number(fan.level)));
        row++;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(a.Getticket().size());
    ui->tableWidget->setHorizontalHeaderLabels({"号码","类型"});

    row=0;
    a.SortTicket();
    for(const Fan &fan:a.Getticket())
    {
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(fan.number)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::number(fan.level)));
        row++;
    }
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(a.Getvip().size());
    ui->tableWidget_2->setHorizontalHeaderLabels({"号码","类型"});
    row=0;
    a.SortVip();
    for(const Fan &fan:a.Getvip())
    {
        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::number(fan.number)));
        ui->tableWidget_2->setItem(row,1,new QTableWidgetItem(QString::number(fan.level)));
        row++;
    }
}

void TicketSale::on_pushButton_2_clicked()
{
    int command = rand() % 2;
    Fan fan1=a.buyTicket(command);
    Fan fan2=a.buyVIP(command);
    ui->tableWidget_3->clear();
    ui->tableWidget_3->setRowCount(2);
    ui->tableWidget_3->setHorizontalHeaderLabels({"号码","类型"});
    if(fan1.number==-1&&fan2.number==-1)
    {
        ui->tableWidget_3->setItem(0,0,new QTableWidgetItem("票卖"));
        ui->tableWidget_3->setItem(0,1,new QTableWidgetItem("完了"));
    }
    else
    {
        ui->tableWidget_3->setItem(0,0,new QTableWidgetItem(QString::number(fan1.number)));
        ui->tableWidget_3->setItem(0,1,new QTableWidgetItem(QString::number(fan1.level)));
    }
    if(fan2.number!=-1)
    {
        ui->tableWidget_3->setItem(1,0,new QTableWidgetItem(QString::number(fan2.number)));
        ui->tableWidget_3->setItem(1,1,new QTableWidgetItem(QString::number(fan2.level)));
    }
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(a.Getticket().size());
    ui->tableWidget->setHorizontalHeaderLabels({"号码","类型"});
    int row;
    row=0;
    for(const Fan &fan:a.Getticket())
    {
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(fan.number)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::number(fan.level)));
        row++;
    }
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(a.Getvip().size());
    ui->tableWidget_2->setHorizontalHeaderLabels({"号码","类型"});
    row=0;
    for(const Fan &fan:a.Getvip())
    {
        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::number(fan.number)));
        ui->tableWidget_2->setItem(row,1,new QTableWidgetItem(QString::number(fan.level)));
        row++;
    }
}

