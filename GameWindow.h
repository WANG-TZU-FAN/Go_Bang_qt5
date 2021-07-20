#ifndef MY_MAINWINDOW_H
#define MY_MAINWINDOW_H

#include "computer.h"
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QVector>
#include <QPair>
#include <QSet>
#include <QMessageBox>
#include <QString>
#include <QMenu>
#include <QDebug>
#include <QStack>
#include <QVector>
#include <QPalette>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QTimerEvent> 


class GameWindow : public QWidget 
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = 0);
	void remake();
    ~ GameWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *mouseEvent);
	
	int count = 0;
	
    int x, y;
	
	// Vector that store chesses
	QVector<QPair<int, int>> reg_Human;
	QVector<QPair<int, int>> reg_Computer;

private:
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	QTime end_time;
	QLabel *time_left;
	QTimer *timer;

	QPainter *painter;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// set a computer player
	computer playerCom;
	
	// set a game window
    GameWindow *gamewindow;
    
    
	// set bottons
    QPushButton *StartBotton;
	QPushButton *RetractBotton;
	QPushButton *CloseBotton;
	
	// set a flag
    int flag = 1;
	
	// computer go first or not 
	int computer_first = 0;
	
};

#endif // MY_MAINWINDOW_H
