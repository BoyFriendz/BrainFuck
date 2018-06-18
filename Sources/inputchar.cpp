#include "inputchar.h"
#include "ui_inputchar.h"


InputChar::InputChar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputChar)
{
    ui->setupUi(this);
}

InputChar::~InputChar()
{
    delete ui;
}

void InputChar::on_buttonBox_accepted()
{

}
