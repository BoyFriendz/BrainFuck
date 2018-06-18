#ifndef INPUTCHAR_H
#define INPUTCHAR_H

#include <QDialog>

namespace Ui {
class InputChar;
}

class InputChar : public QDialog
{
    Q_OBJECT

public:
    explicit InputChar(QWidget *parent = 0);
    ~InputChar();
    Ui::InputChar *ui;
private slots:
    void on_buttonBox_accepted();
};

#endif // INPUTCHAR_H
