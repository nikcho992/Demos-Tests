/*create <DB>;
create <TABLE>;
insert <OBJ> in <TABLE>;
delete <OBJ> from <TABLE>;
select <OBJ> from <TABLE>;
delete <TABLE>;
delete <DB>;
create students; ---> creates an empty file called students.txt

class Command{

string name;
parse();
execute();
};

class CreateTableCmd
{
    string tableName;
};
class InsertCmd
{
    string tableName;
    string elemId;
};
class DeleteCmd
{
    string tableName;
    string elemId;
};
class SelectCmd
{
    string tableName;
    string elemId;
};
class DeleteTableCmd
{
    string tableName;
};

virtual void parse()=0; //in the base class,this method does nothing but in the inherited classes it works.



*/

#include <iostream>
#include <cstring>
#include <string>
#include <cassert>

using namespace std;

class Command
{
protected:
    string name;
public:
    Command(string name)
    {
        this->name=name;
    }

    virtual bool parse(string command)=0;
    virtual bool execute()=0;
};

class CreateTableCmd:public Command
{
private:
    string tableName;
public:
    bool parse(string command)
    {
        int index=command.find(" ");
        name=command.substr(0,index);
        tableName=command.substr(index+1,command.size());

        return !tableName.isEmpty() && tableName.find(" ")!=-1;

    }

    bool execute()
    {
        fstream file("tableName.txt");
        file.close();

        return true;
    }
};

class InsertCmd:public Command
{
private:
    string tableName;
    string elemId;
public:
    bool parse(string command)
    {
        int index=command.find(" ");
        name=command.substr(0,index);
        command=command.substr(index+1,command.size());
        index=command.find(" ");
        elemId=command.substr(0,index);

        command=command.substr(index+1,command.size());
        index=command.find(" ");

        tableName=command.substr(index+1,command.size());
    }

};
