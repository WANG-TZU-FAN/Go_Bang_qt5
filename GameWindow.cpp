#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent){
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialize time
	this->timer = new QTimer(this);

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialize
    remake();
	
	// Set the start botton
    StartBotton = new QPushButton(this);
	// Set the botton name
    StartBotton -> setText("Start");
	// Set the botton position
    StartBotton -> setGeometry(30, 500, 50, 40);
	// Set the botton click function
    connect(StartBotton,&QPushButton::clicked,[=](){
	///////////////////////////////////////////////////////////////////////////////////////////////////////
		timer->stop();
		disconnect(timer, 0, 0, 0);
		this->end_time = QTime(0, 0, 15);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
        flag = 0;
        remake();
	///////////////////////////////////////////////////////////////////////////////////////////////////////
		connect(timer, &QTimer::timeout,[=](){
			this->end_time = this->end_time.addSecs(-1);
			update();
			if (this->end_time.secsTo(QTime(0, 0, 0)) == 0) {
				timer->stop();
				disconnect(timer, 0, 0, 0);
				if(QMessageBox::information(NULL,"Game Over","Timeout","Again","Exit")==1){
					close();
					return;
				}
				else{
					remake();
					return;
				}
			}
		});
		timer->start(1000);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
    });
	
	// Set the retract botton
    RetractBotton = new QPushButton(this);
	// Set the botton name
    RetractBotton -> setText("Retract");
	// Set the botton position
    RetractBotton -> setGeometry(215, 500, 50, 40);
	// botton click function
    connect(RetractBotton,&QPushButton::clicked,[=](){
	///////////////////////////////////////////////////////////////////////////////////////////////////////
		timer->stop();
		disconnect(timer, 0, 0, 0);
		this->end_time = QTime(0, 0, 15);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
		if(computer_first == 0){
			if(!reg_Human.empty()&&reg_Human.size() > 1)
			{
				playerCom.back((reg_Human[reg_Human.size() - 1]).first,(reg_Human[reg_Human.size() - 1]).second);
				reg_Human.pop_back();
			}
			if(!reg_Computer.empty()&&reg_Computer.size() > 1)
			{
				playerCom.back((reg_Computer[reg_Computer.size() - 1]).first,(reg_Computer[reg_Computer.size() - 1]).second);
				reg_Computer.pop_back();
			}
		}
		else{
			if(!reg_Human.empty()&&reg_Human.size() > 0)
			{
				playerCom.back((reg_Human[reg_Human.size() - 1]).first,(reg_Human[reg_Human.size() - 1]).second);
				reg_Human.pop_back();
			}
			if(!reg_Computer.empty()&&reg_Computer.size() > 1)
			{
				playerCom.back((reg_Computer[reg_Computer.size() - 1]).first,(reg_Computer[reg_Computer.size() - 1]).second);
				reg_Computer.pop_back();
			}
		}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
		// Start timing
		update();
		connect(timer, &QTimer::timeout,[=](){
			this->end_time = this->end_time.addSecs(-1);
			update();
			if (this->end_time.secsTo(QTime(0, 0, 0)) == 0) {
				timer->stop();
				disconnect(timer, 0, 0, 0);
				if(QMessageBox::information(NULL,"Game Over","Timeout","Again","Exit")==1){
					close();
					return;
				}
				else{
					remake();
				}
			}
		});
		timer->start(1000);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
    });
	
	
	// Set the close botton
    CloseBotton = new QPushButton(this); 
	// Set the botton name
    CloseBotton -> setText("Close");
	// Set the botton position
    CloseBotton -> setGeometry(400, 500, 50, 40);
	// botton click function
    connect(CloseBotton,&QPushButton::clicked,[=](){
         close();
    });
}

/* Intitialization */
void GameWindow::remake()
{	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	this->end_time = QTime(0, 0, 15);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	computer_first = 0;
    reg_Human.clear();
    reg_Computer.clear();
	// Gobang Initialization
    playerCom.init();                                           
    if(!flag&&(!QMessageBox::information(NULL,"Again","Who go first?","Computer","Player")))
    {
		computer_first = 1;
		
        reg_Computer << (qMakePair(8*30, 8*30));
    }
    this -> update();
}


GameWindow::~GameWindow()
{
    delete gamewindow;
}

/* Paint the game window objects */
void GameWindow::paintEvent(QPaintEvent *){
	
	// Paint the background
    QPalette palette(this -> palette());
	// setting of background color
    palette.setColor(QPalette::Background, qRgb(255,210,90));
    this -> setPalette(palette);
	
	// Paint the line
    QPainter painter(this);
    QPen pen;
	// Setting of line color
    pen.setColor(Qt::black);
    painter.setPen(pen);
	
	// Paint the checkerboard
	// Horizontal Line
    for(int i = 30;i < 480; i+=30){
        QPoint pointOne(30,i);
        QPoint pointTwo(450,i);
        painter.drawLine(pointOne,pointTwo);
    }
	// Vertical Line
    for(int i = 30; i < 480; i+=30){
        QPoint pointOne(i,30);
        QPoint pointTwo(i,450);
        painter.drawLine(pointOne,pointTwo);
    }
	
	// Paint the chesses
    QBrush brush;
	if(computer_first == 1)
		brush.setColor(Qt::black);
	else
		brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    for(QVector<QPair <int ,int> >::iterator iter=reg_Computer.begin();iter!=reg_Computer.end();iter++)
    {
        painter.drawEllipse((*iter).first-10,(*iter).second-10,15,15);
    }
	
	
	// Cannot retract if only one chess
	if(!reg_Computer.empty())
	{
		brush.setColor(Qt::blue);
		painter.setBrush(brush);
		painter.drawEllipse((reg_Computer[reg_Computer.size() - 1]).first - 10,(reg_Computer[reg_Computer.size() - 1]).second - 10, 15, 15);
	}
	
	
	if(computer_first == 0)
		brush.setColor(Qt::black);
	else
		brush.setColor(Qt::white);
    painter.setBrush(brush);
    for(QVector<QPair<int ,int>>::iterator iter = reg_Human.begin(); iter != reg_Human.end(); iter++)
    {
        painter.drawEllipse((*iter).first - 10,(*iter).second - 10, 15, 15);
    }
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	painter.drawText(0, 10, QString("Left_Time : %1").arg(this->end_time.toString("ss")));
	///////////////////////////////////////////////////////////////////////////////////////////////////////
}
/* Clicking Events*/
void GameWindow::mousePressEvent(QMouseEvent *mouseEvent)
{
	// check if open first time
    if(flag){
		return ;
	}
    x = int(float(mouseEvent->x())/30+0.5)*30;
    y = int(float(mouseEvent->y())/30+0.5)*30;
    QString infoShow;
    if(x >= 30 && x <= 450 && y >= 30 && y <= 450 && count == 0){
	///////////////////////////////////////////////////////////////////////////////////////////////////////
		timer->stop();
		this->end_time = QTime(0, 0, 15);
		timer->start(1000);
	///////////////////////////////////////////////////////////////////////////////////////////////////////

		int t=playerCom.getChessPosition(x,y);
		if(t == -1){
			return ;
		}
		reg_Human << (qMakePair(x,y)),count=0;
		y = (t/15 + 1)*30;x = (t%15 + 1)*30;
		reg_Computer << (qMakePair(x,y));
		t = playerCom.win();
		if(t)
		{
	///////////////////////////////////////////////////////////////////////////////////////////////////////
			timer->stop();
	///////////////////////////////////////////////////////////////////////////////////////////////////////
			if(t == 1){ 
				infoShow = "You Lose";
			}
			else {
				infoShow = "Congradulations!";
			}
			if(QMessageBox::information(NULL,"Game Over",infoShow,"Again","Exit")==1){
				close();
			}
			else{
				remake();
			}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
			timer->start(1000);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
		}
        this -> update();
    }
}
