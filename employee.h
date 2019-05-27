#ifndef EMPLOYEE_H
#define EMPLOYEE_H
# include <QString>
using namespace std;
class Employee
{
private:
    int id,age,salary;
    QString name,lastname;
public:
    Employee();
    Employee(int i,QString n,QString l,int a,int s);
    int getid();
    QString getname();
    QString getlastname();
    int getage();
    int getsalary();
    void setid(int g);
    void setname(QString g);
    void setlastname(QString g);
    void setage(int g);
    void setsalary(int g);
    QString toString();
};

#endif //EMPLOYEE_H
