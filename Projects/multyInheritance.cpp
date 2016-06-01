#include <iostream>
#include <cstring>

using namespace std;

class Vehicle
{
private:
	char* name;
	char* model;
	double height;
	double weight;
	double maxSpeed;
public:

	void setName(char* name)
	{
		delete this->name;
		this->name=new char[strlen(name)+1];
		strcpy(this->name,name);
	}

	void setModel(char* model)
	{
		delete this->model;
		this->model=new char[strlen(model)+1];
		strcpy(this->model,model);
	}

	void setHeight(double height)
	{
		this->height=height;
	}

	void setWeight(double weight)
	{
		this->weight=weight;
	}

	void setMaxSpeed(double maxSpeed)
	{
		this->maxSpeed=maxSpeed;
	}

	Vehicle()
	{
		name=NULL;
		model=NULL;
		height=0;
		weight=0;
		maxSpeed=0;
	}

	Vehicle (char* name,char* model,double height,double weight,double maxSpeed):name(NULL),model(NULL)
	{
		this->setName(name);
		this->setModel(model);
		this->setHeight(height);
		this->setWeight(weight);
		this->setMaxSpeed(maxSpeed);
	}

	Vehicle (const Vehicle& other):name(NULL),model(NULL)
	{
		this->setName(other.name);
		this->setModel(other.model);
		this->setHeight(other.height);
		this->setWeight(other.weight);
		this->setMaxSpeed(other.maxSpeed);
	}

	Vehicle& operator =(const Vehicle& other)
	{
		if(this != &other)
		{
			delete name;
			delete model;

		this->setName(other.name);
		this->setModel(other.model);
		this->setHeight(other.height);
		this->setWeight(other.weight);
		this->setMaxSpeed(other.maxSpeed);

		}

		return *this;
	}

	virtual ~Vehicle ()=0;
	
	double getHeight() const
	{
		return height;
	}

	double getWeight() const
	{
		return weight;
	}

	virtual double getMaxSpeed()
	{
		return maxSpeed;
	}

	bool canPassUnderBridge(float h) const 
	{
		return this->getHeight() < h;
	}

	bool canPassOverBridge(float t) const
	{
		return this->getWeight() < t;
	}

};

Vehicle::~Vehicle()
{
	delete name;
	delete model;
}

class LandVehicle:public Vehicle
{
private:
	int hp;
public:

	LandVehicle(char* name,char* model,double height,double weight,int hp):Vehicle(name,model,height,weight)
	{
		this->hp=hp;
	}

	LandVehicle (const LandVehicle& other):Vehicle(other)
	{
		this->hp=other.hp;
	}

	LandVehicle& operator =(const LandVehicle& other)
	{
		if(this != &other)
		{
			Vehicle::operator=(other);
			this->hp=other.hp;
		}
		return* this;
	}



	float getTime(float km) const
	{
		float result=0;

		return result=km/(this->getMaxSpeed()/60);
	}

};

class WaterVehicle:public Vehicle
{
private:
	double volume;
public:
	WaterVehicle(char* name,char* model,double height,double weight,double volume):Vehicle(name,model,height,weight)
	{
		this->volume=volume;
	}

	WaterVehicle (const WaterVehicle& other):Vehicle()
	{
		this->volume=other.volume;
	}

	WaterVehicle& operator =(const WaterVehicle& other)
	{
		if(this != &other)
		{
			Vehicle::operator=(other);
			this->volume=other.volume;

		}

		return *this;
	}

	double getVolume() const
	{
		return volume;
	}

	virtual double getMaxSpeed() const
	{
		return Vehicle::getMaxSpeed()*0.5;
	}

	float getSpeedUpStream(float speedStream) const
	{
		
		return this->getMaxSpeed() - speedStream; 
		
	}

	float getSpeedDownStream(float speedStream) const
	{
		return this->getMaxSpeed() + speedStream;
	}

	float getTimeUpStream(float miles,float speedStream)
	{
		return miles/(this->getMaxSpeed()-speedStream);
	}

	float getTimeDownStream(float miles,float speedStream)
	{
		return miles/(this->getMaxSpeed()+speedStream);
	}

};

class AmphibiousVehicle:public LandVehicle,public WaterVehicle
{
public:
AmphibiousVehicle(char* name,char* model,double height,double weight,int hp,double volume):Vehicle(name,model,height,weight),LandVehicle(hp),WaterVehicle(volume);

AmphibiousVehicle (const AmphibiousVehicle& other):LandVehicle(other),WaterVehicle(other);

AmphibiousVehicle& operator=(const AmphibiousVehicle& other)
{
	if(this != &other)
	{
		LandVehicle::operator=(other);
		WaterVehicle::operator=(other);
	}

	return *this;
}
virtual double getMaxSpeed()
{
	return Vehicle::getMaxSpeed();
}

double getWaterMaxSpeed()
{
	return WaterVehicle::getMaxSpeed();
}



};
