#include "employee.h"
#include <QString>
using namespace std;
Employee::Employee()
{
    id=0;
    name="";
    lastname="";
    age=NULL;
    salary=NULL;
}
Employee::Employee(int i,QString n,QString l,int a,int s)
{
    id=i;
    name=n;
    lastname=l;
    age=a;
    salary=s;
}

int Employee::getid()
{
    return id;
}

QString  Employee::getname()
{
    return name;
}
QString  Employee::getlastname()
{
    return lastname;
}
int  Employee::getage()
{
    return age;
}
int  Employee::getsalary()
{
    return salary;
}
void Employee::setid(int g)
{
    id=g;
}
void Employee::setname(QString g)
{
     name=g;
}
void Employee::setlastname(QString g)
{
    lastname=g;
}
void Employee::setage(int g)
{
     age=g;
}
void Employee::setsalary(int g)
{
     salary=g;
}

QString Employee::toString()
{
   return QString::number(id)+","+name+","+lastname+","+QString::number(age)+","+QString::number(salary);
}
