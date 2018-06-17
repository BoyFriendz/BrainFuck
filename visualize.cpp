#include "visualize.h"
#include "ui_visualize.h"
#include<windows.h>

Visualize::Visualize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Visualize)
{
    ui->setupUi(this);
}

Visualize::~Visualize()
{
    delete ui;
}


void Visualize::on_pushButton_clicked()
{
    QByteArray ba = qcode.toLatin1();
    char Sresult[100]={""};
    char *code=ba.data();
    char *adr = (char *)malloc(strlen(code) * sizeof(char));
    char temp[2] = { "" };
    int i, k, j;
        int ptr = 0;
        int illegalinput = 0;
        for (i = 0; i <(int)strlen(code); i++)
            adr[i] = 0;
        for (i = 0; i < (int)strlen(code); i++) {
            switch (code[i])
            {
            case '>':
                ++ptr;
                break;
            case '<':
                --ptr;
                break;
            case '+':
                ++adr[ptr];
                break;
            case '-':
                --adr[ptr];
                break;
            case '.':
                temp[0] = adr[ptr];
                strcat(Sresult, temp);
                break;
            case ',':
                break;
            case '[':
                k = 0, j = 0;
                if (adr[ptr] == 0) {
                    k = 1, j = 0;
                    i++;
                    while (k != j) {
                        if (code[i] == ']')
                            k++;
                        if (code[i] == '[')
                            j++;
                        i++;
                    }
                    i--;
                }
                break;
            case ']':
                if (adr[ptr] != 0) {
                    k = 1, j = 0;
                    i--;
                    while (k != j) {
                        if (code[i] == ']')
                            k++;
                        if (code[i] == '[')
                            j++;
                        i--;
                    }
                    i++;
                }
                break;
            default:
                illegalinput++;
                break;
            }
            speedcontroller=ui->Box->value();
            Sleep(speedcontroller);
            ui->textBrowser->setPlainText(QString(QLatin1String(Sresult)));
            ui->cell1_2->display((int)adr[0]);
            ui->cell2_2->display((int)adr[1]);
            ui->cell3_2->display((int)adr[2]);
            ui->cell4->display((int)adr[3]);
            ui->cell5->display((int)adr[4]);
            ui->cell6->display((int)adr[5]);
            qApp->processEvents();
        }
}

