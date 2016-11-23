#include <iostream>
#include <stack>

using namespace std;

#define MAX_SIZE 4

int  maze[MAX_SIZE][MAX_SIZE] = {	0, 0, 0, 0,
								   	1, 1, 1, 0,
								  	0, 1, 1, 0,
								  	0, 0, 0, 0};

void printMaze()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		for (int j = 0; j < MAX_SIZE; ++j)
		{
			cout<<maze[i][j]<<" ";
		}
		cout<<endl;
	}
}

bool possibleMovement(int x,int y)
{
	return x >= 0 &&
		   y >= 0 &&
		   x < MAX_SIZE &&
		   y < MAX_SIZE &&
		   maze[x][y] == 0;
}

bool downstairs(int sx,int sy,int px,int py)
{
	if(sx == px && sy == py)
		return true;

	if(possibleMovement(sx+1,sy))
		return downstairs(sx+1,sy,px,py);

	if(possibleMovement(sx,sy+1))
		return downstairs(sx,sy+1,px,py);

	return false;

}

// START WORKING WITH STACK

struct Operation
{
	int x;
	int y;

	Operation(int _x,int _y):x(_x),y(_y){}
};

bool downstairsStack(int sx,int sy,int px,int py)
{
	stack<Operation> opertaions;
	opertaions.push(Operation(sx,sy));

	while(!opertaions.empty())
	{
		Operation topOperation = opertaions.top();
		opertaions.pop();

		if(topOperation.x == px && topOperation.y == py)
			return 1;

		else if(possibleMovement(topOperation.x +1,topOperation.y))
		{
			opertaions.push(Operation(topOperation.x + 1,topOperation.y));
		}
		else if(possibleMovement(topOperation.x,topOperation.y +1))
		{
			opertaions.push(Operation(topOperation.x,topOperation.y +1));
		}
	}
	if(opertaions.empty())
		return false;
}


// FINISH WORKING WITH STACK

int main()
{
	printMaze();
	cout<<"++++++++++++++++++"<<endl;
	cout<<downstairsStack(2,0,3,1)<<endl;
	cout<<downstairsStack(3,1,0,0)<<endl;
}
