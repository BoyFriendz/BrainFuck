#ifndef INPUTNUM_H
#define INPUTNUM_H

#include <QDialog>

namespace Ui {
class InputNum;
}

class InputChar : public QDialog
{
    Q_OBJECT

public:
    explicit InputChar(QWidget *parent = 0);
    ~InputChar();
    Ui::InputNum *ui;
};

#endif // INPUTNUM_H
