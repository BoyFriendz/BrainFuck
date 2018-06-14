#include "brainfuck.h"
#include "ui_brainfuck.h"

BrainFuck::BrainFuck(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrainFuck)
{
    ui->setupUi(this);
}

BrainFuck::~BrainFuck()
{
    delete ui;
}
