#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BrainFuck.h"
#include <QMainWindow>
#include <QApplication>
#include <QtGui>
#include <QtWidgets>
namespace Ui
{
	class BrainFuck;
}

class BrainFuck : public QMainWindow
{
	Q_OBJECT

public:
	BrainFuck(QWidget *parent = Q_NULLPTR);
	~BrainFuck();

private:
	Ui::BrainFuckClass *ui;

private slots:
	void on_actionRun_triggered();
	void on_actionOpen_triggered();
	void on_actionSave_triggered();
	void on_actionUndo_triggered();
	void on_actionRedo_triggered();
	void on_actionCut_triggered();
	void on_actionCopy_triggered();
	void on_actionPaste_triggered();
    void on_actionHelp_triggered();
};
