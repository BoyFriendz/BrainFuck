#include "visualize.h"
#include "ui_visualize.h"
#include<windows.h>
#include<inputchar.h>
#include<ui_inputchar.h>

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

int comma_1(char *code) {
    int comma = 0;
    for (int i = 0; i <(int) strlen(code); i++)
        if (code[i] == ',')
            comma++;
    return comma;
}

void Visualize::BFShow(char* code,char* input){
    char temp[2]="";
    char *adr = (char *)malloc(strlen(code) * sizeof(char));
    char Sresult[100]={""};
    int i, k, j,n=0;
        int ptr = 0;
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
                adr[ptr] = input[n++];
                break;
            case '[':
                k = 0, j = 0;
                if (adr[ptr] == 0) {
                    k = 1, j = 0;
                    i++;
                    while (k != j) {
                        if (code[i] == ']')
                            j++;
                        if (code[i] == '[')
                            k++;
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
            }
            speedcontroller=ui->Box->value();
            Sleep(500/speedcontroller);                //控制演示速度
            ui->textBrowser->setPlainText(QString(QLatin1String(Sresult)));
            ui->cell1_2->display((int)adr[0]);        //每一个cell对应一个内存地址的数值
            ui->cell2_2->display((int)adr[1]);
            ui->cell3_2->display((int)adr[2]);
            ui->cell4->display((int)adr[3]);
            ui->cell5->display((int)adr[4]);
            ui->cell6->display((int)adr[5]);
            qApp->processEvents();
        }
}
void Visualize::on_pushButton_clicked()
{
    QByteArray ba = qcode.toLatin1();

    char *code=ba.data();

    char* input="";
    if(comma_1(code)){                        //出现逗号特别处理
        InputChar *I = new InputChar(this);
        I->exec();
        QString str = I->ui->textEdit->toPlainText();
        QByteArray byt = str.toLatin1();
        input= byt.data();
        BFShow(code,input);
    }
    else{
        BFShow(code,input);
    }

}

