#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <QDialog>
#include<Qspinbox>
#include<Qslider>
namespace Ui {
class Visualize;
}

class Visualize : public QDialog
{
    Q_OBJECT

public:
    explicit Visualize(QWidget *parent = 0);
    ~Visualize();
    int info=0;
    QString qcode="";
    Ui::Visualize *ui;
   int speedcontroller=4;
	
private slots:
    void on_pushButton_clicked();
};

#endif // VISUALIZE_H
