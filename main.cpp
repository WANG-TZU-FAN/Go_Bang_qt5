#include <QApplication>
#include "GameWindow.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);  

	GameWindow gamewindow;
	
	gamewindow.setWindowTitle("Gomoku");

	gamewindow.resize(480, 600);
  
	gamewindow.show();

	return app.exec();
}

