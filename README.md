# Go_Bang_qt5

109 school year, Semester 2nd
National Cheng Kung University
Electeical Engineering

COMPUTER SCIENCEⅡ
Project 2: Gomoku !

王梓帆（Wang Tzu Fan）

 

Report Deadline : 2021/06/15 
 
Catalog
Contents
第一章	Frame of the Project	1
1-1	Computer	1
1-2	GameWindow	2
第二章 Explanation	3
2-1	Function in Computer	3
2-2	Problems in Computer.cpp	3
2-2-1	Initialization	3
2-2-2	Insertion	3
2-2-3	Put Nearby Positions Out of or Into Candidate Set	4
2-2-4	Get the chess position	4
2-2-5	If the chess is legal	4
2-2-6	If the chess is legal	4
2-2-7	Bonus : Undo	4
2-3	Bonus : Ability of computer - MinMax Algorithm	5
2-3-1	Basic of this algorithm	5
2-3-2	How this algorithm works in my program	5
2-3-3	How decisions being made	5
2-4	Function in GameWindow	6
2-5	Problems in GameWindow.cpp	6
2-5-1	Bonus : Decide order with animation	6
2-5-2	Bonus : Time Limitation	7
2-5-3	The setting of chess table and chesses	7
第二章	Project Result	7
第三章	Program Feedback and Reflection	8


Picture Catalog
圖 2-1 1 The Blak and White Chess	3
圖 2-2 1 Computer will play the first step beside your chesses	4
圖 2-3 1 Schematic diagram of MinMax Algorithm	5
圖 2-4 1 Interface of Gumoku	6
圖 2-5 1 Playing Process of the Gomoku	7

  
第一章	Frame of the Project
1-1	Computer
Computer
-   int : getScoreTable( int )
-   int : grid[15][15]
-   dx_stick : int
-   QSet<int> : Chess_Set
-   QSet<int> : Candi_Set
-   int : countChessNumber[5]
-   int : Side_1, Side_2
-   int : Side_11, Side_22
-   char : str
-   int : Chess_X,Chess_Y
-   int : find_Up ( int , int )
-   int : find_Down ( int , int )
-   int : find_Right ( int , int )
-   int : find_Left ( int , int )
-   int : find_Left_Up ( int , int )
-   int : find_Right_Down ( int , int )
-   int : find_Right_Up ( int , int )
-   int : find_find_Left_Down ( int , int )
<< constructor >> + computer ( )
+   init ( ) : void
+   insert ( int , int ) : void
+   setStick_dx ( int ) : void
+   putNearbyPositionsOutofCandi ( ) : void
+   putNearbyPositionsIntoCandi ( ) : void
+   getChessPosition ( int , int ) : int
+   legal ( int , int ) : int
+   minput ( int ) : int
+   maxput ( int ) : int
+   getEvaluateScore ( ) : int
+   countScore ( int , int ) : int
+   win ( ) : int
+   retract ( int , int ) : int
 
1-2	GameWindow
Ball
-   GameWindow : *gamewindow
-   Qtime : end_time
-   QLabel : *time_left
-   Qtimer : *timer
-   QPainter : *painter
-   computer : playerCom
-   QpushButton : *StartBotton
-   QpushButton : *RetractBotton
-   QpushButton : *CloseBotton
-   flag : int
-   computer_first : int
<< constructor >> +  GameWindow ( QWidget *parent = 0)
<< distructor >>  +  ~ GameWindow()
+   remake() : void
+	paintEvent(QPaintEvent *) : void
+	mousePressEvent(QMouseEvent *mouseEvent): void
+	int : count
+	int : x
+   int : y
+   Qvector < Qpair < int , int >> : reg_Human
+   Qvector < Qpair < int , int >> : reg_Computer
 
第二章 Explanation
2-1	Function in Computer
In this class, I am trying to creat a computer player in my game. At the very beginning, it has only simple playing function in this class. The model at first is too weak, so that the player can beat it easily. However, after using algorithms, it has become robuster. I will explain in more details in my report.
 
圖 2-1 1 The Blak and White Chess

2-2	Problems in Computer.cpp
The problems encountered here are mainly in algorithms, but still some details should be discussed. I will explain them step by step

2-2-1	Initialization
The are four elements should be initialized. The first one is the “ Chess_Set ”, it is used to store the chesses already played. The second one is thee “Candi_Set”, it is used to store the data of candidate sets for chesses that will be played in the future. The third one is the “grid”, it representes the 15 * 15 matrix that store our playes. The last but not least, is the ChessPosition that represents the number of positions from 0 to 224.

2-2-2	Insertion
To insert the chess, it will put nearby positions into the candidate set, and set the grid positions to ‘$’ sign. $ and @ sign is to determine whether that position is used by computer or human . Those signs are important . Both “putNearbyPositionsOutofCandi” and “putNearbyPositionsIntoCandi” are my ways of setting candidate set. I will explain them in next two subsections.
 
2-2-3	Put Nearby Positions Out of or Into Candidate Set
These two function make the decision of put elements into or out of candidate sets. This will make computer seems like more defensible than attactive, but improve the ability of the computer player a little. Because of those blocking chesses, human player may win in more diffucult way. 
The basic of this method, is to move the empty position with no chess pieces nearby out of the candidate set, and move the empty position near the positions that have been used into the candidate set. By using accumulation of ChessPosition[positionNumber], we can decide to remove or move in.
 
圖 2-2 1 Computer will play the first step beside your chesses

2-2-4	Get the chess position
This function is to get the positions that have been played by computers. The most important thing is to check in mouse press event. If it returns -1, the game will not start to determine the terminate state.

2-2-5	If the chess is legal
This function is to check if the position that we played is legal. That is, the chess is in the size of chess board.

2-2-6	If the chess is legal
This function is to check if the position that we played is legal. That is, the chess is in the size of chess board.

2-2-7	Bonus : Undo
This function is to retract the decision. that is to remove the chess, and do the same process before previous plays.
2-3	Bonus : Ability of computer - MinMax Algorithm 
This algorithm is a common way of determing playes of computer. This algorithm costs me the most time in my whole project. According to this reason, I will explain this algorithm in a separate chapter.

2-3-1	Basic of this algorithm
MinMax is a decision rule used in game theory, for minimizing the possible loss for a worst case (maximum loss) scenario. When dealing with gains, it is referred to as "maximin"—to maximize the minimum gain. Originally formulated for n-player zero-sum game theory, covering both the cases where players take alternate moves and those where they make simultaneous moves, it has also been extended to more complex games and to general decision-making in the presence of uncertainty.

2-3-2	How this algorithm works in my program
At first, we need to calculate the score of each steps, so we need to find fuctions to calculate the chesses in the same line. after accumulation, we will match each configuration to specific scores. The rules of grading, is that more chesses in the same line will get more grades. If blocked by one side, the grading will decade 1 level. If two sides were blocked, it wull get zero points. After grading, we need to tell the computer to choose the position.

2-3-3	How decisions being made
The following is the schematic diagram of this algorithm.
 
圖 2-3 1 Schematic diagram of MinMax Algorithm
	In the diagram, “甲” represents the computer, “乙” in other way represents the human player. If it is computer’s turn, it will always choose the maximun nodes. On the other hand, If it is human player’s turn, it will always choose the minimun nodes. These decisions will build a decision tree, and our target, is to find the maximum and minimum of the score. After counting scores, we can end the game if the score matches the score of winning condition ( 5 chesses in the same line), we can determine whether winner is computer or human. 
2-4	Function in GameWindow 
In this class, I am trying to set the interface of my game.
 
圖 2-4 1 Interface of Gumoku
1.	Left_Time for counting player’s time consume.
2.	Grid for player’s and computer to play the chess.
3.	Start for making decision of who is first.
4.	Retract for undo previous plays.
5.	Close for close the window.

2-5	Problems in GameWindow.cpp
2-5-1	Bonus : Decide order with animation
I can decide the order, but still cannot decide in animation. It still has some problems in different players. Take the chess color as example, the color should be changed in different first player.
 
2-5-2	Bonus : Time Limitation
It takes an afternoon for debugging time limitation. We need to include a special header file Qtime for the timer, and set starts and stops in correct code segments.

2-5-3	The setting of chess table and chesses
The reason why I didn’t use the chess board provided by TA’s, is that I was getting dizzy of counting and matching the pixels. Finally, I found an alternative way by using functions in Qpainter! Like brush, setColor, drawLine, drawEllipse, etc. However, it seems that this way of painting still waste a lot of time. The Best advantage is that I can draw on a paper first, then set the position in more accurate way.

第二章	Project Result
 
 

The first step of the game is to choose the first player is computer or human.	 

 	 	You can choose “Again” for another match, or choose “Exit” for quitting. In the game, you can press “Retract” for undo previous plays. It will follow the rule of specifications.
圖 2-5 1 Playing Process of the Gomoku
 
第三章	Program Feedback and Reflection
In this project, I think the most difficult part is the implementation of the algorithm. Since that I am not familiar in this algorithm, so I used a lot of time understanding the concept of this algorithm. Problems I mentioned in the report are big questions, however, there were a lot of bugs when implementing actually. This is the final project of this semester, I think that I learned a new coding environment, and learned a great lesson.
Extremely grateful of teacher and TA’s. According to the epidemic, it has a lot of difficulties in the classes. This course had made the wisest decision, and very take care of students. Thank wou very much.
