#include <iostream>
#include <stack>

using namespace std;


struct Operation
{
	static const int OPER_PLACE_KNIGHT = 0;
	static const int OPER_REMOVE_KNIGHT = 1;
	static const int OPER_FIND_SOLUTION = 2;

	int row;
	int column;
	int operType;
	int numKnights;
	int boardSize;


	Operation(int type,int num,int size,int r,int c)
			:operType(type),numKnights(num),boardSize(size),row(r),column(c){}

	Operation(int type,int num,int size):operType(type),numKnights(num),boardSize(size){}

};

class KnightConfigurator
{
private:

	static const int MAX_SIZE = 8;

	bool board[MAX_SIZE][MAX_SIZE];
	stack<Operation> operations;
	bool hasKnight(int row,int column,int boardSize) const;
	bool canPlaceKnight(int row,int column,int boardSize) const;
	bool isValid(int row,int column,int boardSize) const;

public:
    KnightConfigurator(int knights,int size);
	void printCurrentConfiguration(int size) const;
	void findNextConfiguration(int numKnights,int size) ;
	bool hasNextConfiguration() const;
};

KnightConfigurator::KnightConfigurator(int knights,int size)
{
    for(int row = 0; row < size; ++row)
        {
            for(int column = 0; column < size; ++column)
                {
                    board[row][column] = false;
                }
        }

     operations.push(Operation(Operation::OPER_FIND_SOLUTION,knights,size));
     findNextConfiguration(knights,size);
}

bool KnightConfigurator::hasKnight(int row,int column,int boardSize) const
{
	return row >= 0 &&
		   column >= 0 &&
		   row < boardSize &&
		   column < boardSize &&
		   board[row][column];
}

bool KnightConfigurator::canPlaceKnight(int row,int column,int size) const
{
	return !hasKnight(row-1,column+2,size) &&
		   !hasKnight(row+1,column+2,size) &&
		   !hasKnight(row+2,column+1,size) &&
		   !hasKnight(row+2,column-1,size) &&
		   !hasKnight(row-1,column-2,size) &&
		   !hasKnight(row+1,column-2,size) &&
		   !hasKnight(row-2,column+1,size) &&
		   !hasKnight(row-2,column-1,size) &&
		   !hasKnight(row,column,size);
}

bool KnightConfigurator::isValid(int row,int column,int boardSize) const
{
	return row >= 0 &&
		   column >= 0 &&
		   row < boardSize &&
		   column < boardSize;
}

void KnightConfigurator::printCurrentConfiguration(int size) const
{
	cout<<"+++++++++++++++++++"<<endl;

	for(int row = 0; row < size; ++row)
	{
		for (int column = 0; column < size; ++column)
		{
			if(hasKnight(row,column,size))
                cout<<"H ";
            else
                cout<<"- ";
		}
		cout<<endl;
	}

	cout<<"++++++++++++++++++++"<<endl;
}

void KnightConfigurator::findNextConfiguration(int numKnights,int size)
{
	operations.push(Operation(Operation::OPER_FIND_SOLUTION,numKnights,size));

	while(!operations.empty())
	{
		Operation topOperation = operations.top();
		int numKnights = topOperation.numKnights;
		int size = topOperation.boardSize;
		operations.pop();

		if(numKnights == 0)
		{
			printCurrentConfiguration(size);
		}
		else if(topOperation.operType == Operation::OPER_PLACE_KNIGHT)
		{
			board[topOperation.row][topOperation.column] = true;

		}
		else if(topOperation.operType == Operation::OPER_REMOVE_KNIGHT)
		{
			board[topOperation.row][topOperation.column] = false;

		}
		else
		{
			for(int row = 0; row < size; ++row)
			{
				for (int column = 0; column < size; ++column)
				{
					if(canPlaceKnight(row,column,size))
					{
						operations.push(Operation(Operation::OPER_REMOVE_KNIGHT,1,size,row,column));
						operations.push(Operation(Operation::OPER_FIND_SOLUTION,numKnights-1,size));
						operations.push(Operation(Operation::OPER_PLACE_KNIGHT,1,size,row,column));
					}
				}
			}
		}
	}
}

bool KnightConfigurator::hasNextConfiguration() const
{
	stack<Operation> copyStack = operations;

	while(!copyStack.empty())
	{
		Operation nextOperation = copyStack.top();
		copyStack.pop();

		if(nextOperation.operType != Operation::OPER_REMOVE_KNIGHT)
			return true;
	}
	return false;
}

int main()
{
   KnightConfigurator configurator(2,3);
   //configurator.printCurrentConfiguration(4);

	while(configurator.hasNextConfiguration())
	{
		//cout << "+++++++++++++++++++++++" << endl;
		//configurator.printCurrentConfiguration(3);
		cout << "+++++++++++++++++++++++" << endl;
		configurator.findNextConfiguration(2,3);
}

}
