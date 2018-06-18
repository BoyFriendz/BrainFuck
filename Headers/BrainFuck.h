#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_BrainFuck.h"
#include <QMainWindow>
#include <QApplication>
#include <QtGui>
#include <QtWidgets>
#include<QCloseEvent>

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
    int checked = 0;
    void newFile();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);

private:
	Ui::BrainFuckClass *ui;
    bool isUntitled;
    QString curFile;

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
    void on_actionShow_triggered();
    void on_actionCheck_triggered();
    void on_actionNew_triggered();
    void on_actionSave_As_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();

protected:
    void closeEvent(QCloseEvent *event);
};
