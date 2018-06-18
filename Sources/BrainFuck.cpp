#include"BrainFuck.h"
#include<qfile.h>
#include <qstring.h>
#include"help.h"
#include<visualize.h>
#include<ui_visualize.h>
#include<inputchar.h>
#include<ui_inputchar.h>
#include<BFCore.h>
#include<QTextStream>

BrainFuck::BrainFuck(QWidget *parent) //设置主窗口，新建名为Unnamed的bf文件
	: QMainWindow(parent),
	ui(new Ui::BrainFuckClass)
{
	ui->setupUi(this);
    isUntitled = true;
    curFile = tr("Unnamed.bf");
    setWindowTitle(curFile);
}

BrainFuck::~BrainFuck()
{
	delete ui;
}

void BrainFuck::newFile()                                     //创建新的bf文件
{
    if(maybeSave()){
        isUntitled = true;
        curFile = tr("Unnamed.bf");
        checked=0;
        ui->resultEdit->clear();
        ui->codeEdit->clear();
        ui->codeEdit->setVisible(true);
    }
}

bool BrainFuck::maybeSave()                                 //判断是否保存过
{
                                                            // 如果文档被更改了
    if (ui->codeEdit->document()->isModified()) {
                                                             // 自定义一个警告对话框
        QMessageBox box;
        box.setWindowTitle(tr("Warning!"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile + tr("Have not saved it，save first？"));
        QPushButton *yesBtn = box.addButton(tr("YES(&Y)"),
                                            QMessageBox::YesRole);
        box.addButton(tr("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBut = box.addButton(tr("CANCEL(&N)"),
                                               QMessageBox::RejectRole);
        box.exec();
        if (box.clickedButton() == yesBtn)
            return save();
        else if (box.clickedButton() == cancelBut)
            return false;
    }
                                         // 如果BF没有被更改，则直接返回true
    return true;
}

bool BrainFuck::save()  //保存文件
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool BrainFuck::saveAs()  //文件另存为
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save as"),curFile);
    if (fileName.isEmpty()) return false;
    return saveFile(fileName);
}

bool BrainFuck::saveFile(const QString &fileName) //保存文件的函数
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {

                                                                // 判断是否可读写
        QMessageBox::warning(this, tr("BrainFuck Interpreter"),
                             tr("Can not write or read！ %1：/n %2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->codeEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    isUntitled = false;
    // 获得文件的标准路径
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}


void BrainFuck::on_actionRun_triggered()   //运行解释器
{   char output[]="Need check first!";
    if(checked){
	QString qcode = ui->codeEdit->toPlainText();
	QByteArray ba = qcode.toLatin1();
	char *code=ba.data();
    char temp[100]="";
    if(comma(code)){                        //出现逗号特别处理
        InputChar *I = new InputChar(this);
        I->exec();
        QString str = I->ui->textEdit->toPlainText();
        QByteArray ba = str.toLatin1();
        char *ch = ba.data();
        BFexecute(code,ch);
        ui->resultEdit->setPlainText(QString(QLatin1String(result)));
    }
    else{
    BFexecute(code,temp);
    ui->resultEdit->setPlainText(QString(QLatin1String(result)));
    }
    }
    else ui->resultEdit->setPlainText(QString(QLatin1String(output)));
}

void BrainFuck::on_actionUndo_triggered()     //以下几个函数皆为文本处理
{
	ui->codeEdit->undo();
}

void BrainFuck::on_actionRedo_triggered()
{
	ui->codeEdit->redo();
}

void BrainFuck::on_actionCut_triggered()
{
	ui->codeEdit->cut();
}

void BrainFuck::on_actionCopy_triggered()
{
	ui->codeEdit->copy();
}

void BrainFuck::on_actionPaste_triggered()
{
	ui->codeEdit->paste();
}

void BrainFuck::on_actionOpen_triggered()       //打开文件
{   ui->resultEdit->setText(tr(""));
    checked=0;
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("BrainFuck Files(*.bf)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
			return;
        }                         //判断是否可读可写
		QTextStream in(&file);
		ui->codeEdit->setText(in.readAll());
        QApplication::restoreOverrideCursor();
        curFile=QFileInfo(path).canonicalFilePath();
        setWindowTitle(curFile);
        ui->codeEdit->setVisible(true);
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
	}
}

void BrainFuck::on_actionSave_triggered()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.bf)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Write File"), tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream out(&file);
		out << ui->codeEdit->toPlainText();
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
	}
}


void BrainFuck::on_actionHelp_triggered()     //给出BF的基本语法规则
{
    help *h = new help(this);
    h->show();
}

void BrainFuck::on_actionShow_triggered()      //展示内存变化，输出过程
{   if(checked){
    Visualize *v = new Visualize(this);
    v->show();
    v->setWindowTitle("Visualize");
    v->qcode=ui->codeEdit->toPlainText();
    QByteArray ba = v->qcode.toLatin1();
    char *code=ba.data();
    QSpinBox *spinBox = new QSpinBox();
    QSlider *slider = new QSlider();
    spinBox=v->ui->Box;
    slider=v->ui->Slider;
    v->ui->Box->setRange(1,501);
    v->ui->Slider->setRange(1,501);       //速度调试器
    v->ui->Box->setValue(10);
    QObject::connect(slider,&QSlider::valueChanged,spinBox,&QSpinBox::setValue);
    void(QSpinBox::*spinBoxSignal)(int)=&QSpinBox::valueChanged;
    QObject::connect(spinBox, spinBoxSignal, slider, &QSlider::setValue);}
    else ui->resultEdit->setText(tr("Need check first!"));
}


void BrainFuck::on_actionCheck_triggered()   //检查代码是否正确
{
    char output1[]="Brackets can not match!";
    char output2[]="Illegal Char!";
    char output3[]="ERRPR TYPE";
    char output5[]="Checked valid!";
    QString qcode = ui->codeEdit->toPlainText();
    QByteArray ba = qcode.toLatin1();
    char *code=ba.data();
    if(!check(code)){
        ui->resultEdit->setPlainText(QString(QLatin1String(output1)));
        ui->label->setText(QString(QLatin1String(output3)));
    }
    else if(illegalcount(code)){
        ui->resultEdit->setPlainText(QString(QLatin1String(output2)));
        ui->label->setText(QString(QLatin1String(output3)));
    }
    else {checked = 1;ui->resultEdit->setText(QString(QLatin1String(output5)));
        ui->label->setText(tr("Result"));
    }
}

void BrainFuck::on_actionNew_triggered()
{
    newFile();
}

void BrainFuck::on_actionSave_As_triggered()
{
    saveAs();
}

void BrainFuck::on_actionClose_triggered()
{
    if (maybeSave()) {
        ui->codeEdit->setVisible(false);
    }
}

void BrainFuck::on_actionExit_triggered()
{
    on_actionClose_triggered();
    qApp->quit();
}

void BrainFuck::closeEvent(QCloseEvent *event)
{
                                            // 如果maybeSave()函数返回true，已保存，则关闭程序
    if (maybeSave()) {
        event->accept();
    } else {                                // 否则忽略该事件
        event->ignore();
    }
}
