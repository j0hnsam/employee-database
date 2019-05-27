#ifndef DATABASE_H
#define DATABASE_H

# include <QSqlDatabase>
# include <QSqlQuery>
# include <QSqlError>
# include "employee.h"
class Database
{
private:
    QSqlDatabase db;
public:
    Database();
    void    setName(QString name);
    void    insertEmployee(Employee &e);
    QVector<Employee> employees();
    Employee  getEmployee(int id,bool &found);
    void    updateEmployee(int id,Employee &e);
    void    deleteEmployee(int id);
    ~Database();
};

#endif // DATABASE_H
