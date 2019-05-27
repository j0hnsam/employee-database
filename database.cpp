# include "database.h"
# include <QVariant>
# include <QDebug>
Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

void    Database::setName(QString name)
{
    if(db.isOpen()) db.close();
    db.setDatabaseName(name);
    db.open();
    QSqlQuery q(db);
    q.exec(QString("create table if not exists employee(")+
                        QString("id integer primary key autoincrement,")+
                        QString("name varchar(1024),lastname varchar(1024),")+
                        QString("age integer,salary integer)")
                        );
}

void    Database::insertEmployee(Employee &e)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO employee (id,name,lastname,age,salary) VALUES (:id,:name,:lastname,:age,:salary)");
    query.bindValue(":id",e.getid());
    query.bindValue(":name", e.getname());
    query.bindValue(":lastname",e.getlastname());
    query.bindValue(":age",e.getage());
    query.bindValue(":salary",e.getsalary());
    query.exec();

}

QVector<Employee> Database::employees()
{
    QVector<Employee> e;
    QSqlQuery query(db);
    query.exec("SELECT id,name,lastname,age,salary FROM employee");
    while (query.next())
    {
        Employee E(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toInt(),query.value(4).toInt());
        e.append(E);
    }
    return e;
}

void    Database::updateEmployee(int id,Employee &e)
{
 QSqlQuery query(db);
 query.exec("UPDATE employee set  name='"+e.getname()+"',lastname='"+e.getlastname()+"',id='"+QString::number(e.getid())+"',age='"+QString::number(e.getage())+"',salary='"+QString::number(e.getsalary())+"' where id="+QString::number(id));
}

void    Database::deleteEmployee(int id)
{
    QSqlQuery query(db);
    query.exec("DELETE from employee  where id="+QString::number(id));
}

Database::~Database()
{
    db.close();
}
Employee  Database::getEmployee(int id,bool &found)
{
 QSqlQuery query(db);
 query.exec("SELECT id,name,lastname,age,salary FROM employee where id="+QString::number(id));
 if(query.next()==true)
  {
    Employee C(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toInt(),query.value(4).toInt());
     found=true;
   return C;
 }
 else found=false;

}
