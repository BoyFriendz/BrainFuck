#include "BrainFuck.h"
#include "BFCore.h"
#include<qfile.h>
#include <qstring.h>
#include"help.h"
BrainFuck::BrainFuck(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
}

BrainFuck::~BrainFuck()
{
	delete ui;
}

void BrainFuck::on_actionRun_triggered()
{
	QString code = ui->codeEdit->toPlainText();
	int inputNum = inputCalculate(code.toStdString());
	QString result = QString::fromStdString(BFexecute(code.toStdString(), ""));
	ui->resultEdit->setPlainText(result);
}

void BrainFuck::on_actionUndo_triggered()
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

void BrainFuck::on_actionOpen_triggered()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.bf)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream in(&file);
		ui->codeEdit->setText(in.readAll());
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


void BrainFuck::on_actionHelp_triggered()
{
    help *h = new help(this);
    h->show();
}
