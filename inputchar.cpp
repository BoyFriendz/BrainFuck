#include "inputchar.h"
#include "ui_inputchar.h"

InputChar::InputChar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputNum)
{
    ui->setupUi(this);
}

InputChar::~InputChar()
{
    delete ui;
}
