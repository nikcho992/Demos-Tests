#include <iostream>
#include <cstring>

using namespace std;

class Diagnostic
{
private:
	char* name;
	double price;
	double time;
public:
	void setName(char* name)
	{
		delete this->name;
		this->name=new char[strlen(name)+1];
		strcpy(this->name,name);
	}

	void setPrice(double price)
	{
		this->price=price;
	}

	void setTime(double time)
	{
		this->time=time;
	}

	void copy(const Diagnostic& other)
	{
		this->setName(other.name);
		this->setPrice(other.price);
		this->setTime(other.time);
	}

	Diagnostic()
	{
		name=NULL;
		price=NULL;
		time=NULL;
	}

	Diagnostic(char*name,double price,double time):name(NULL)
	{
		this->setName(name);
		this->setPrice(price);
		this->setTime(time);
	}

	Diagnostic(const Diagnostic& other):name(NULL)
	{
		copy(other);
	}

	Diagnostic& operator= (const Diagnostic& other)
	{
		copy(other);
		return *this;
	}

	~Diagnostic()
	{
		delete[] name;
	}

	char* getName() const
	{
		return name;
	}

	double getTime() const
	{
		return time;
	}

	virtual double calcPrice()
	{
		return price;
	}


};

class SingleDiagnostic : public Diagnostic
{
private:
	double minValue;
	double maxValue;
public:
	SingleDiagnostic(char* name,double price,double time,double minValue,double maxValue):Diagnostic(name,price,time)
	{
		this->minValue=minValue;
		this->maxValue=maxValue;
	}

	SingleDiagnostic(const SingleDiagnostic& other):Diagnostic(other)
	{
		this->minValue=other.minValue;
		this->maxValue=other.maxValue;
	}

	SingleDiagnostic& operator=(const SingleDiagnostic& other)
	{
		if(this != &other)
		{
			Diagnostic::operator=(other);
			this->minValue=other.minValue;
			this->maxValue=other.maxValue;
		}
		return *this;
	}

	void setMinValue(double min)
	{
	    minValue=min;
	}
	void setMaxValue(double max)
	{
	    maxValue=max;
	}

	double getMinValue() const
	{
		return minValue;
	}

	double getMaxValue() const
	{
		return maxValue;
	}

	virtual double calcPrice()
	{
		return Diagnostic::calcPrice();
	}

};

class Package : public Diagnostic
{
private:
	Diagnostic* tests;
	int testsCounter;
	int testsNumber;
public:

	Package()
	{
		tests=NULL;
		int testsCounter=0;
		int testsNumber=0;

	}

	Package(int testsCounter,int testsNumber)
	{
		this->testsNumber=testsNumber;
		tests= new Diagnostic[testsNumber];
		this->testsCounter=testsCounter;
	}

	virtual double calcPrice()
	{
		double res=0.0;

		if(testsNumber>0)
		{
			for (int i = 0; i < testsNumber; ++i)
		{
			res+=tests[i].calcPrice();
		}

		return res-res*0.1;
		}
		return NULL;
	}

	double calcTime()
	{
		double maxTime=0.0;

		if(testsNumber>0)
		{
			for (int i = 0; i < testsNumber; ++i)
			{
			if(tests[i].getTime()>tests[i+1].getTime())
				{
				maxTime=tests[i].getTime();
				}
			}
		return maxTime;
		}
		return NULL;
	}

	~Package()
	{
		delete[] tests;
	}
};

class Queue : public Diagnostic
{
private:
	Diagnostic **tests;
	int counter;
	int number;
public:
	Queue()
	{
		tests=NULL;
		counter=0;
		number=0;
	}

	Queue(int number,int counter)
	{
		this->number=number;
		tests=new Diagnostic* [number];
		this->counter=counter;
	}

	virtual double calcPrice()
	{
		double res=0.0;

		if(number>0)
		{
			for (int i = 0; i < number; ++i)
			{
				res+=tests[i]->calcPrice();
			}
		}

		return res;
	}

	double calcTime()
	{
		double minTime=0.0;

		if(number>0)
		{
			for (int i = 0; i < number; ++i)
			{
			if(tests[i]->getTime()<tests[i+1]->getTime())
				{
				minTime=tests[i]->getTime();
				}
			}
		return minTime;
		}
		return NULL;
	}

	void resize (int minSize)
	{

		Diagnostic** newTests = new Diagnostic* [minSize];

		for (int i = 0; i < number; i++)
			newTests[i] = tests[i];

		delete []tests;

		tests = newTests;

		number = minSize;
	} //мислих да ползвам този метод при добавянето и премахването ама не можах да ги измисля

//	void addDiagnostic(Diagnostic other)
//	{
//
//	}


};
