#ifndef COMPUTER_H
#define COMPUTER_H
#include <QSet>
class computer
{
public:
    computer();
    void init();
    void back(int x, int y);
	int getChessPosition(int x, int y);
    void insert(int x, int y);
	int win();
	int legal(int i, int j);
	void putNearbyPositionsOutofCandi(int n, int m);
    void putNearbyPositionsIntoCandi(int n, int m);
	int minput(int n);
	int maxput(int n);
    int getEvaluateScore();
    int countScore(int n, int m);
	
private:
	
	// Find Functions
	int find_Up(int n,int m),find_Down(int n,int m);
	int find_Right(int n,int m),find_Left(int n,int m);
	int find_Left_Up(int n,int m), find_Right_Down(int n,int m);
	int find_Right_Up(int n,int m), find_Left_Down(int n,int m);
	
	// Score Table
	int getScoreTable(int i);

    // chessboard
	char grid[15][15];
	
	QSet<int> Chess_Set;
	QSet<int> Candi_Set;
	
	int countChessNumber[5];
	
	// Check Blocked side
    int Side_1, Side_2;
	int side_11, side_22;
    
	char str;
	
    int Chess_X,Chess_Y;
	
	int ChessPosition[225];
};
#endif // COMPUTER_H
