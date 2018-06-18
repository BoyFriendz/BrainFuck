#include "BrainFuck.h"
#include <QtWidgets/QApplication>
#include"inputchar.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BrainFuck w;
	w.show();

	return a.exec();
}
