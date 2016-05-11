#include <iostream>
#include <cstring>
#include <assert.h>

using namespace std;

class Ship
{
public:
    char *name;
    int year;
    int numWeapons;
public:

    Ship()
    {
        name=" ";
        year=0;
        numWeapons=0;
    }

    Ship(char*name,int year,int numWeapons)
    {
        this->name=name;
        this->year=year;
        this->numWeapons=numWeapons;
    }

    Ship (const Ship& other)
    {
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name,other.name);

        this->year=other.year;
        this->numWeapons=other.numWeapons;

    }

    Ship& operator = (const Ship& other)
    {
        this->name=other.name;
        this->year=other.year;
        this->numWeapons=other.numWeapons;
    }

    ~Ship()
    {
        delete name;
    }

    void setName(char* name)
    {
        this->name=name;
    }

    void setYear(int year)
    {
        this->year=year;
    }

    void setNumWeapons(int numWeapons)
    {
        this->numWeapons=numWeapons;
    }

    char* getName()
    {
        return name;
    }

    int getYear()
    {
        return year;
    }

    int getNumWeapons()
    {
        return numWeapons;
    }

    void print()
    {
        cout<<"Name: "<<name<<" "<<"Year: "<<year<<" "<<"Num weapons: "<<numWeapons<<endl;
    }
};

class Navy
{
private:
    char* country;
    Ship* ships;
    int shipCounter;
public:

    Navy(char*country,int numShips,int shipCounter)
    {
        this->country=new char(strlen(country)+1);
        strcpy(this->country,country);

        ships=new Ship[numShips];

        this->shipCounter=shipCounter;
    }

    ~Navy()
    {
    	delete country;
    	delete ships;
    }

    char* getCountry()
    {
        return country;
    }

    void addShip(const Ship& other)
    {
        for (int i = 0; i < shipCounter; ++i)
        {

        		assert((other.name!=ships[i].name));

        }

        ships[shipCounter].name=other.name;
        ships[shipCounter].year=other.year;
        ships[shipCounter].numWeapons=other.numWeapons;

        shipCounter++;
    }

    void removeShip(char* name)
    {
        int temp=0;

        for (int i = 0; i < shipCounter; ++i)
        {
            if(name==ships[i].getName())
            {
                temp=i;
            }
        }

        for (int i = temp; i < shipCounter-1 ; ++i)
        {
            ships[i]=ships[i+1];
        }

        shipCounter--;
    }

    void swap(Ship& first, Ship& second)
    {
        Ship temp(" ",0,0);

        temp=second;
        second=first;
        first=temp;

	}

    void sortByWeapons()
    {
            for (int j = 0; j < shipCounter-1; ++j)
            {
                if(ships[j+1].getNumWeapons()<ships[j].getNumWeapons())
                {
                    swap(ships[j],ships[j+1]);
                }
            }

    }

    void print()
    {
        for (int i = 0; i < shipCounter; ++i)
        {
            cout<<"Ship name: "<<ships[i].getName()<<" "<<"Year: "<<ships[i].getYear()<<" "<<"Number of weapons: "<<ships[i].getNumWeapons()<<endl;
        }
    }

};

int main()
{
    Ship shark("shark",1948,200);
    Ship hammer("hammer",2008,80);
    Ship lightning("lightning",1996,99);
    Ship thunder("thunder",1933,400);
    //shark.print();

    Navy arr("Bulgaria",2,0);
    Navy arr2("Germany",2,0);

    cout<<"Navy of "<<arr.getCountry()<<endl;

    arr.addShip(shark);
    arr.addShip(hammer);
    arr2.addShip(lightning);
    arr2.addShip(thunder);
    //arr.sortByWeapons();
   // arr2.removeShip("thunder");


	arr.print();
    cout<<endl;

    cout<<"Navy of "<<arr2.getCountry()<<endl;
    arr2.print();

    shark.~Ship();
    hammer.~Ship();
    lightning.~Ship();
    thunder.~Ship();

    arr.~Navy();
    arr2.~Navy();


}
