#include "computer.h"

// Constructor
computer::computer()
{
    init();
}

// Initialization
void computer::init()
{	
    Chess_Set.clear();
    Candi_Set.clear();
    memset(grid, '-', sizeof(grid));
    memset(ChessPosition, 0, sizeof(ChessPosition));
}

// Retraction
void computer::back(int x, int y)
{
    int i = y / 30 - 1;
    int j = x / 30 - 1;
    grid[i][j] = '-';
    putNearbyPositionsOutofCandi(i, j);
    Candi_Set.clear();
	// erase the chess in the chess set
    Chess_Set.erase(Chess_Set.find(i*15 + j));
    for(QSet<int>::iterator it = Chess_Set.begin(); it != Chess_Set.end(); it++){
        int temp = *it;
        i = temp/15;
		j = temp%15;
        putNearbyPositionsIntoCandi(i,j);
    }
}

// 把 Gomoku 下的棋子回傳給 computer
int computer::getChessPosition(int x, int y)
{
    int i, j;
	i = y / 30 - 1;
    j = x / 30 - 1;
	
    if(grid[i][j]!='-'){
		return -1;
	}
	
    grid[i][j] = '@';
	
    Chess_Set.insert((i)*15 + j);
	
    putNearbyPositionsIntoCandi(i, j);
	
    Chess_X = 0;
	Chess_Y = 0;
	
    maxput(3);
	
    putNearbyPositionsIntoCandi(Chess_X, Chess_Y);
	
    Chess_Set.insert(Chess_X*15 + Chess_Y);
	
    Candi_Set.erase(Candi_Set.find(Chess_X*15 + Chess_Y));
	
    grid[Chess_X][Chess_Y]='$';
	
	// Return the position of computer chess
    return Chess_X*15 + Chess_Y;

}

// Insert the chesses that have been put on chessboard 
void computer::insert(int x,int y)
{
    putNearbyPositionsIntoCandi(x,y);
    Chess_Set.insert(x*15 + y);
    grid[x][y]='$';
}

// return 1: Computer win, return 0: player win 
int computer::win()
{
    int temp;
	int i, j;
	int state = 0;
    for(QSet<int>::iterator it = Chess_Set.begin(); it != Chess_Set.end(); it++)
    {
        temp = *it;
        i = temp/15;
		j = temp%15;
        if(grid[i][j] == '$' && countScore(i,j) >= 100000){
			state = 1;
		}
        else if(grid[i][j] == '@' && countScore(i,j) >= 100000){
			state = 0;
		}
    }
    return state;
}

// If legal position
int computer:: legal(int i, int j)
{
    if(i >= 0 && j >= 0 && i < 15 && j < 15){	
		return 1;
	}
    return 0;
}

// 把附近沒有棋子的空白位置移出候補集合
// Move the empty position with no chess pieces nearby out of the candidate set
// Check 8 directions in Clockwise
void computer::putNearbyPositionsOutofCandi(int n, int m)
{
	// 把中心移出候補集合
	Candi_Set.erase(Candi_Set.find(112));
	
    if(legal(n - 1, m - 1) && grid[n - 1][m - 1] == '-'){
		int positionNumber = (n - 1)*15 + m - 1;
		ChessPosition[positionNumber]--;
		if(ChessPosition[positionNumber] == 0){
			Candi_Set.erase(Candi_Set.find(positionNumber));
		}
    }
	
    if(legal(n - 1, m) && grid[n - 1][m] == '-'){
        int positionNumber = (n - 1)*15 + m;
		ChessPosition[positionNumber]--;
		if(ChessPosition[positionNumber] == 0){
			Candi_Set.erase(Candi_Set.find(positionNumber));
		}
    }
	
    if(legal(n - 1, m + 1) && grid[n - 1][m + 1] == '-'){
		int positionNumber = (n - 1)*15 + m + 1;
		ChessPosition[positionNumber]--;
		if(ChessPosition[positionNumber] == 0){
			Candi_Set.erase(Candi_Set.find(positionNumber));
		}
    }
	
    if(legal(n, m + 1) && grid[n][m + 1] == '-'){
        int positionNumber = (n)*15 + m + 1;
		ChessPosition[positionNumber]--;
		if(ChessPosition[positionNumber] == 0){
			Candi_Set.erase(Candi_Set.find(positionNumber));
		}
    }
	
    if(legal(n + 1, m + 1) && grid[n + 1][m + 1] == '-'){
		int positionNumber = (n + 1)*15 + m + 1;
		ChessPosition[positionNumber]--;
		if(ChessPosition[positionNumber] == 0){
			Candi_Set.erase(Candi_Set.find(positionNumber));
		}
    }
	
    if(legal(n + 1, m) && grid[n + 1][m] == '-'){
        int positionNumber = (n + 1)*15 + m;
        ChessPosition[positionNumber]--;
		if(ChessPosition[positionNumber] == 0){
			Candi_Set.erase(Candi_Set.find(positionNumber));
		}
    }
	
    if(legal(n + 1, m - 1) && grid[n + 1][m - 1] == '-'){
        int positionNumber = (n + 1)*15 + m - 1;
		ChessPosition[positionNumber]--;
		if(ChessPosition[positionNumber] == 0){
			Candi_Set.erase(Candi_Set.find(positionNumber));
		}
    }
	
	if(legal(n, m - 1) && grid[n][m - 1] == '-'){
		int positionNumber=(n)*15 + m - 1;
        ChessPosition[positionNumber]--;
		if(ChessPosition[positionNumber] == 0){
			Candi_Set.erase(Candi_Set.find(positionNumber));
		}
    }
}

// 把已經下的棋子附近的空白位置移入候補集合
// Move the empty position near the positions that have been used into the candidate set
// Check 8 directions in Clockwise
void computer::putNearbyPositionsIntoCandi(int n, int m)
{
    if(legal(n - 1, m - 1) && grid[n - 1][m - 1] == '-')
    {
        int positionNumber = (n - 1)*15 + (m - 1);
        Candi_Set.insert(positionNumber);
        ChessPosition[positionNumber]++;
    }
	
    if(legal(n - 1, m) && grid[n - 1][m] == '-')
    {
        int positionNumber = (n - 1)*15 + (m);
        Candi_Set.insert(positionNumber);
		ChessPosition[positionNumber]++;
    }
	
    if(legal(n - 1, m + 1) && grid[n - 1][m + 1] == '-')
    {
        int positionNumber = (n - 1)*15 + (m + 1);
        Candi_Set.insert(positionNumber);
		ChessPosition[positionNumber]++;
    }
	
    if(legal(n, m + 1) && grid[n][m + 1] == '-')
    {
        int positionNumber = (n)*15 + (m + 1);
        Candi_Set.insert(positionNumber);
		ChessPosition[positionNumber]++;
    }
	
    if(legal(n + 1, m + 1) && grid[n + 1][m + 1] == '-'){
        int positionNumber = (n + 1)*15 + (m + 1);
		Candi_Set.insert(positionNumber);
		ChessPosition[positionNumber]++;
    }
	
    if(legal(n + 1, m) && grid[n + 1][m] == '-')
    {
        int positionNumber = (n + 1)*15 + (m);
        Candi_Set.insert(positionNumber);
		ChessPosition[positionNumber]++;
    }
	
    if(legal(n + 1, m - 1) && grid[n + 1][m - 1] == '-')
    {
        int positionNumber = (n + 1)*15 + (m - 1);
        Candi_Set.insert(positionNumber);
		ChessPosition[positionNumber]++;
    }

    if(legal(n, m - 1) && grid[n][m - 1] == '-')
    {
        int positionNumber = (n)*15 + (m - 1);
        Candi_Set.insert(positionNumber);
		ChessPosition[positionNumber]++;
    }
}

// 玩家下棋時的最好狀況
// 極大值極小值演算法的 min 函數
int computer::minput(int n)
{
    if(n==1) return getEvaluateScore();
    int positionNumber;
	int temp = 100000000;
	int k, i, j;

	for(QSet<int>::iterator it2=Candi_Set.begin();it2!=Candi_Set.end();it2++)
	{
		positionNumber = *it2;
		i = positionNumber/15;
		j = positionNumber%15;
        if(grid[i][j]=='-')
        {
            grid[i][j]='@';
            putNearbyPositionsIntoCandi(i, j);
            Chess_Set.insert(positionNumber);
            k = maxput(n - 1);
            putNearbyPositionsOutofCandi(i, j);
            if(temp > k){
                temp = k;
            }
            grid[i][j]='-';
            Chess_Set.erase(Chess_Set.find(positionNumber));
        }
    }
    return temp;
}

// 電腦下棋時的最好狀況
// 極大值極小值演算法的 max 函數
int computer:: maxput(int n)
{
    if(n == 1){
		return getEvaluateScore();
	}
	int positionNumber;
    int temp = -100000000;
	int k,i,j;
    for(QSet<int>::iterator it2=Candi_Set.begin(); it2!=Candi_Set.end(); it2++)
    {
		positionNumber = *it2;
        i = positionNumber/15;
		j = positionNumber%15;
        if(grid[i][j]=='-')
        {
            grid[i][j]='$';
            putNearbyPositionsIntoCandi(i,j);
            Chess_Set.insert(positionNumber);
            k = minput(n-1);
            putNearbyPositionsOutofCandi(i,j);
            if(temp < k)
            {
                temp = k;
                if(n == 3){
					Chess_X = i;
					Chess_Y = j;
				}
            }
            grid[i][j]='-';
            Chess_Set.erase(Chess_Set.find(positionNumber));
        }
    }
    return temp;
}

// 評估局勢，進行整個棋盤的評分
int computer::getEvaluateScore()
{
	int ComputerScore = 0;
	int PlayerScore = 0;
	int positionNumber;
	int temp;
    int i, j;
    for(QSet<int>::iterator it = Chess_Set.begin();it != Chess_Set.end(); it++)
    {
        positionNumber = *it;
        i = positionNumber/15;
		j = positionNumber%15;
        if(grid[i][j]=='$')
        {
            temp = countScore(i,j);
            if(temp >= 10000)
            {
                temp+=10000;
            }
            ComputerScore+=temp;
		}
        else if(grid[i][j]=='@'){
			PlayerScore+=countScore(i,j);
		}
    }
	return ComputerScore - PlayerScore;
}

// 進行棋子的評分
int computer::countScore(int n, int m)
{
    int t = 0;
	int k, g, side_111, side_222;
	if(grid[n][m] == '@'){
		str='@';
	}
    else if(grid[n][m] == '$'){
		str='$';
	}
	
	/* 找 \ */
	Side_1 = 0;
	Side_2 = 0;
	side_11 = 0;
    side_22 = 0; 
    countChessNumber[1] = find_Left_Up(n, m) + 1;
    side_111 = side_11;
	side_222 = side_22;
	countChessNumber[1]+=find_Right_Down(n, m);
	k = 0;
	g = 0;
    if(Side_1&&(!Side_2)){
		countChessNumber[1]+=find_Left_Up(side_111, side_222);
	}
    else if(!Side_1&&Side_2){
		countChessNumber[1]+=find_Right_Down(side_11, side_22);
	}
	else if(Side_1&&Side_2){
        k = find_Left_Up(side_111, side_222);
        g = find_Right_Down(side_11, side_22);
        if(k + Side_1 >= g + Side_2){
			countChessNumber[1] += k;
			Side_2 = 1;
		}
        else{
			countChessNumber[1] += g;
			Side_1 = 1;
		}
    }
	t = t + getScoreTable(1);
	
	/* 找 | */
	Side_1 = 0;
	Side_2 = 0;
	side_11 = 0;
	side_22 = 0;
    countChessNumber[2] = find_Up(n,m) + 1;
    side_111 = side_11;
	side_222 = side_22;
	countChessNumber[2]+=find_Down(n,m);
    k = 0;
	g = 0;
	if(Side_1&&(!Side_2)){
		countChessNumber[2]+=find_Up(side_111, side_222);
	}
    else if(!Side_1&&Side_2){
		countChessNumber[2]+=find_Down(side_11,side_22);
	}
	else if(Side_1&&Side_2){
        k = find_Up(side_111, side_222);
        g = find_Down(side_11, side_22);
        if(k + Side_1 >= g + Side_2){
			countChessNumber[2]+=k;
			Side_2 = 1;
		}
        else{
			countChessNumber[2]+=g;
			Side_1 = 1;
		}
    }
	t = t + getScoreTable(2);
	
	/* 找 - */
	Side_1 = 0;
	Side_2 = 0;
	side_11 = 0;
	side_22 = 0;
	countChessNumber[3] = find_Right_Up(n,m) + 1;
	side_111 = side_11;
	side_222 = side_22;
	countChessNumber[3]+=find_Left_Down(n,m);
	k = 0;
	g = 0;
	if(Side_1 && (!Side_2)){
		countChessNumber[3]+=find_Right_Up(side_111,side_222);
	}
	else if((!Side_1) && Side_2){
		countChessNumber[3]+=find_Left_Down(side_11,side_22);
	}
	else if(Side_1 && Side_2){
        k = find_Right_Up(side_111,side_222);
        g = find_Left_Down(side_11,side_22);
        if(k + Side_1 >= g + Side_2){
			countChessNumber[3]+=k;
			Side_2 = 1;
		}
        else{
			countChessNumber[3]+=g;
			Side_1 = 1;
		}
    }
    t = t + getScoreTable(3);
		
	/* 找 / */
	Side_1 = 0;
	Side_2 = 0;
	side_22 = 0;
	side_11 = 0;
    countChessNumber[4] = find_Right(n,m) + 1;
    side_111 = side_11;
	side_222 = side_22;
    countChessNumber[4]+=find_Left(n,m);
    k = 0;
	g = 0;
    if(Side_1 && (!Side_2)){
		countChessNumber[4]+=find_Right(side_111,side_222);
	}
    else if((!Side_1) && Side_2){
		countChessNumber[4]+=find_Left(side_11,side_22);
	}
    else if(Side_1 && Side_2){
        k = find_Right(side_111,side_222);
        g = find_Left(side_11,side_22);
        if(k+Side_1>=g+Side_2){
			countChessNumber[4]+=k;
			Side_2 = 1;
		}
        else{
			countChessNumber[4]+=g;
			Side_1 = 1;
		}
    }
    t = t + getScoreTable(4);
	
	Side_1 = 0;
	Side_2 = 0;
	
    if(t >= 2000 &&t <= 10000){
		t+=8000;
	}
    return t;
}

int computer:: find_Up(int n,int m)
{
    if(legal(n - 1, m) && grid[n - 1][m] == str){
		return 1 + find_Up(n - 1,m);
	}
	if(legal(n - 1, m) && grid[n - 1][m] == '-'){
        Side_1 = 1;
		side_11 = n - 1;
		side_22 = m;
    }
    return 0;
}

int computer:: find_Down(int n,int m)
{
    if(legal(n + 1, m) && grid[n + 1][m] == str){
		return 1 + find_Down(n+1,m);
	}
    if(legal(n + 1, m) && grid[n + 1][m] == '-')
    {
        Side_2 = 1;
		side_11 = n + 1;
		side_22 = m;
    }
    return 0;
}

int computer:: find_Right(int n,int m)
{
    if(legal(n, m + 1) && grid[n][m + 1] == str){
		return 1 + find_Right(n, m + 1);
	}
	if(legal(n,m+1)&&grid[n][m+1]=='-')
    {
        Side_1 = 1;
		side_11 = n;
		side_22 = m + 1;
    }
    return 0;
}

int computer:: find_Left(int n,int m)
{
    if(legal(n, m - 1) && grid[n][m - 1] == str){
		return 1 + find_Left(n, m - 1);
	}
	if(legal(n, m - 1) && grid[n][m - 1] == '-')
    {
        Side_2 = 1;
		side_11 = n;
		side_22 = m - 1;
    }
    return 0;
}

int computer:: find_Left_Up(int n,int m)
{
    if(legal(n - 1, m - 1) && grid[n - 1][m - 1] == str){
		return 1 + find_Left_Up(n - 1,m - 1);
	}
	if(legal(n - 1, m - 1) && grid[n - 1][m - 1] == '-'){
        Side_1 = 1;
		side_11 = n - 1;
		side_22 = m - 1;
	}
	return 0;
}

int computer:: find_Right_Down(int n,int m)
{
    if(legal(n + 1, m + 1) && grid[n + 1][m + 1] == str){
		return 1 + find_Right_Down(n + 1, m + 1);
	}
	if(legal(n + 1, m + 1) && grid[n + 1][m + 1] == '-')
    {
        Side_2 = 1;
		side_11 = n + 1;
		side_22 = m + 1;
    }
    return 0;
}

int computer:: find_Right_Up(int n,int m)
{
    if(legal(n - 1, m + 1) && grid[n - 1][m + 1] == str){
		return 1 + find_Right_Up(n - 1,m + 1);
	}
	if(legal(n - 1, m + 1) && grid[n - 1][m + 1] == '-'){
        Side_1 = 1;
		side_11 = n - 1;
		side_22 = m + 1;
    }
    return 0;
}

int computer:: find_Left_Down(int n,int m)
{
    if(legal(n + 1, m - 1) && grid[n + 1][m - 1] == str){
		return 1 + find_Left_Down(n + 1, m - 1);
	}
	if(legal(n + 1, m - 1) && grid[n + 1][m - 1] == '-')
    {
        Side_2 = 1;
		side_11 = n + 1;
		side_22 = m - 1;
    }
    return 0;
}

int computer::getScoreTable(int i)
{
    if(countChessNumber[i] >= 5){
		return 100000;
	}
    if(countChessNumber[i] == 4)
    {
		// Both sides being blocked
        if(Side_1 && Side_2){
			return 10000;
		}
		// One sides being blocked
        if(Side_1 ^ Side_2){
			return 1000;
		}
        return 0;
    }
    if(countChessNumber[i] == 3)
    {
        if(Side_1 && Side_2){
			return 1000;
		}
        if(Side_1 ^ Side_2){
			return 100;
		}
        return 0;
    }
    if(countChessNumber[i] == 2)
    {
        if(Side_1 && Side_2){
			return 100;
		}
        if(Side_1 ^ Side_2){
			return 10;
		}
        return 0;
    }
    if(countChessNumber[i] == 1)
    {
        if(Side_1 && Side_2)
        {
            return 10;
        }
        if(Side_1 ^ Side_2){
			return 1;
		}
        return 0;
    }
}
