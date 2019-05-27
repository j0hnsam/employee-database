#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(700,300);
    setWindowTitle("Employee");
    mainWidget=new QWidget;
    setCentralWidget(mainWidget);
    mainWidget->setFixedSize(this->width(),this->height());
    mainLayout=new QVBoxLayout;
    mainWidget->setLayout(mainLayout);
    mydb=nullptr;
    makeMenus();
    panel=new QStackedLayout;
    mainLayout->addLayout(panel);
    makeInputForm();
    makeDisplayForm();
    makeSearchForm();
}

void    MainWindow::makeMenus()
{
    fileMenu=new QMenu("FILE");
    editMenu=new QMenu("EDIT");
    fileMenu->addAction("RANDOM");
    fileMenu->addAction("SAVE");
    fileMenu->addAction("LOAD");
    fileMenu->addAction("EXPORT");
    fileMenu->addAction("EXIT");
    connect(fileMenu,SIGNAL(triggered(QAction*)),this,SLOT(fileSlot(QAction*)));

    editMenu->addAction("NEW");
    editMenu->addAction("DISPLAY");
    editMenu->addAction("SEARCH");
    connect(editMenu,SIGNAL(triggered(QAction*)),this,SLOT(editSlot(QAction*)));

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
}

void    MainWindow::makeInputForm()
{
   QWidget *tab1=new QWidget;
   panel->addWidget(tab1);
   tab1->setFixedSize(95*this->size().width()/100,this->size().height()/2);
   QVBoxLayout *tab1layout=new QVBoxLayout;
   tab1->setLayout(tab1layout);

   QHBoxLayout *line1=new QHBoxLayout;
   tab1layout->addLayout(line1);

   QHBoxLayout *line2=new QHBoxLayout;
   tab1layout->addLayout(line2);

   idEdit=new QLineEdit;
   idEdit->setPlaceholderText("ID");
   line1->addWidget(idEdit);

   nameEdit=new QLineEdit;
   nameEdit->setPlaceholderText("Name");
   line1->addWidget(nameEdit);

   lastnameEdit=new QLineEdit;
   lastnameEdit->setPlaceholderText("Lastname");
   line1->addWidget(lastnameEdit);

   ageEdit=new QLineEdit;
   ageEdit->setPlaceholderText("Age");
   line1->addWidget(ageEdit);

   salaryEdit=new QLineEdit;
   salaryEdit->setPlaceholderText("Salary");
   line1->addWidget(salaryEdit);


   addButton=new QPushButton;
   addButton->setText("ADD EMPLOYEE");
   connect(addButton,SIGNAL(clicked(bool)),this,SLOT(addSlot()));
   line2->addWidget(addButton);
}

QString GetRandomName()
{
   QString possiblenames[60]={"George","John","Jackson","Olivia","Max","Liam","Anastasia","Bill","Tom","Maria""Dustin","Cassie","Malka","Deanne","Novella",
                              "Shana","Naoma","Tina","Janey","Jerlene","Librada","Tarra","Garnett","Jacque","Corliss",
                              "Nicola","Timika","Shu","Lorena","Shelli","Brigida","Nora","Janessa","Yee","Lacy","Tammera","Willene",
                              "Ariel","Zada","Chi","Maricela","Pearline","Yuko","Talisha","Ivana","Jeanie","Rodrick",
                              "Sherill","Hettie","Maribeth","Laurel","Nicolas","Emilie","Sharie",
                              "Martha","Lorenza","Sha","Kyle","Garth","Mac"};
   int i= qrand() %59;
   return possiblenames[i];
}
QString GetRandomLastName()
{
    QString possiblelastnames[50]={"Meza","Lyons","Mcbride","Nicholson","Powers","Murillo","Suarez","Gilmore","Salinas","Benson",
                                   "Dyer","Cardenas","Jefferson","Peck","Mayer","Wall","Reid","Moon","Hebert","Roberson","Chavez","Lester","Vasquez",
                                   "Thompson","Valentine","Mcbride","Glover","Greer","Arnold","Bryan","Conley","Richard","Gillespie","Mercado","Huerta",
                                   "Perry","Harmon","Barajas","Gross","Gamble","Miller","Molina","Ortega","Fox","Mejia","Osborne","Porter","Odom","Hall","Esparza"};
    int i= qrand() %49;
    return possiblelastnames[i];
}
void    MainWindow::addSlot()
{
    if(mydb==nullptr)
    {
        QMessageBox::critical(this,"Error","Database not opened");
        return;
    }
    if(nameEdit->text().isEmpty() || lastnameEdit->text().isEmpty() ||
            idEdit->text().isEmpty()||ageEdit->text().isEmpty()||salaryEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"Error","Empty fields");
        return;
    }
    Employee E(idEdit->text().toInt(),nameEdit->text(),lastnameEdit->text(),ageEdit->text().toInt(),salaryEdit->text().toInt());
    QVector<Employee> e=mydb->employees();
    for(int i=0;i<e.size();i++)
        {
        if(e[i].getid()==idEdit->text().toInt())
            {
            QMessageBox::critical(this,"Error","ID of employee already exists.");
            return;
            }
        }
    mydb->insertEmployee(E);
    QMessageBox::information(this,"Employee","New employee added");
    clearSlot();
    reloadTable();
}

void    MainWindow::clearSlot()
{
    idEdit->setText("");
    nameEdit->setText("");
    lastnameEdit->setText("");
    ageEdit->setText("");
    salaryEdit->setText("");
}

void    MainWindow::makeDisplayForm()
{
    QWidget *tab2=new QWidget;
    panel->addWidget(tab2);
    tab2->setFixedSize(95*this->size().width()/100,this->size().height()/2);
    QVBoxLayout *tab2layout=new QVBoxLayout;
    tab2->setLayout(tab2layout);

    table=new QTableWidget;
    table->setRowCount(1);
    table->setColumnCount(6);
    QStringList header;
    header<<"ID"<<"NAME"<<"LASTNAME"<<"AGE"<<"SALARY"<<"";
    table->setHorizontalHeaderLabels(header);
    tab2layout->addWidget(table);

    QHBoxLayout *line1=new QHBoxLayout;
    tab2layout->addLayout(line1);

    QPushButton *updateButton=new QPushButton;
    updateButton->setText("UPDATE EMPLOYEE");
    connect(updateButton,SIGNAL(clicked(bool)),this,SLOT(updateSlot()));
    line1->addWidget(updateButton);
}

void    MainWindow::makeSearchForm()
{
    QWidget *tab3=new QWidget;
    panel->addWidget(tab3);
    tab3->setFixedSize(95*this->size().width()/100,this->size().height()/2);
    QVBoxLayout *tab3layout=new QVBoxLayout;
    tab3->setLayout(tab3layout);
    QHBoxLayout *line1=new QHBoxLayout;
    tab3layout->addLayout(line1);
    QHBoxLayout *line2=new QHBoxLayout;
    tab3layout->addLayout(line2);

    idContainsEdit=new QLineEdit;
    idContainsEdit->setPlaceholderText("ID SEARCH");
    line1->addWidget(idContainsEdit);

    nameContainsEdit=new QLineEdit;
    nameContainsEdit->setPlaceholderText("NAME SEARCH");
    line1->addWidget(nameContainsEdit);

    lastnameContainsEdit=new QLineEdit;
    lastnameContainsEdit->setPlaceholderText("LASTNAME SEARCH");
    line1->addWidget(lastnameContainsEdit);

    ageContainsEdit=new QLineEdit;
    ageContainsEdit->setPlaceholderText("AGE SEARCH");
    line1->addWidget(ageContainsEdit);

    salaryContainsEdit=new QLineEdit;
    salaryContainsEdit->setPlaceholderText("SALARY SEARCH");
    line1->addWidget(salaryContainsEdit);

    searchButton=new QPushButton;
    searchButton->setText("SEARCH");
    connect(searchButton,SIGNAL(clicked(bool)),this,SLOT(searchSlot()));
    line2->addWidget(searchButton);
}
void    MainWindow::searchSlot()
{
    if(mydb==nullptr)
    {
        QMessageBox::critical(this,"Error","Database not opened");
        return ;
    }
    if(idContainsEdit->text().isEmpty() && nameContainsEdit->text().isEmpty() && lastnameContainsEdit->text().isEmpty() && ageContainsEdit->text().isEmpty() && salaryContainsEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"Error","Empty fields");
        return ;
    }
    QString htmlText="<h3 align=center>Results</h3><ol>";
    QVector<Employee> E=mydb->employees();
    bool found=false;
    for(int i=0;i<E.size();i++)
    {
        if(!idContainsEdit->text().isEmpty())
        {
          if(E[i].getid()==(idContainsEdit->text().toInt()))
          {
              htmlText+="<ol>"+E[i].toString()+"</ol>";
              found=true;
          }
        }

        else if(!nameContainsEdit->text().isEmpty())
        {
            if(!lastnameContainsEdit->text().isEmpty())
            {
                if(!ageContainsEdit->text().isEmpty())
                {
                    if(!salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getname().startsWith(nameContainsEdit->text()) && E[i].getlastname().startsWith(lastnameContainsEdit->text()) && E[i].getage()==(ageContainsEdit->text().toInt())&&E[i].getsalary()==(salaryContainsEdit->text().toInt()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                    if(salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getname().startsWith(nameContainsEdit->text()) && E[i].getlastname().startsWith(lastnameContainsEdit->text()) && E[i].getage()==(ageContainsEdit->text().toInt()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                }
                if(ageContainsEdit->text().isEmpty())
                {
                    if(!salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getname().startsWith(nameContainsEdit->text()) && E[i].getlastname().startsWith(lastnameContainsEdit->text())&&E[i].getsalary()==(salaryContainsEdit->text().toInt()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                    if(salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getname().startsWith(nameContainsEdit->text()) && E[i].getlastname().startsWith(lastnameContainsEdit->text()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                }
            }
            if(lastnameContainsEdit->text().isEmpty())
            {
                if(!ageContainsEdit->text().isEmpty())
                {
                    if(!salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getname().startsWith(nameContainsEdit->text()) && E[i].getage()==(ageContainsEdit->text().toInt())&&E[i].getsalary()==(salaryContainsEdit->text().toInt()))
                        {
                             htmlText+="<ol>"+E[i].toString()+"</ol>";
                             found=true;
                        }
                    }
                    if(salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getname().startsWith(nameContainsEdit->text()) && E[i].getage()==(ageContainsEdit->text().toInt()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                }
                if(ageContainsEdit->text().isEmpty())
                {
                    if(!salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getname().startsWith(nameContainsEdit->text()) && E[i].getsalary()==(salaryContainsEdit->text().toInt()))
                            {
                                htmlText+="<ol>"+E[i].toString()+"</ol>";
                                found=true;
                            }
                    }
                    if(salaryContainsEdit->text().isEmpty())
                        {
                            if(E[i].getname().startsWith(nameContainsEdit->text()))
                            {
                                htmlText+="<ol>"+E[i].toString()+"</ol>";
                                found=true;
                            }
                        }
                 }
            }
        }
        else if(nameContainsEdit->text().isEmpty())
        {
            if(!lastnameContainsEdit->text().isEmpty())
            {
                if(!ageContainsEdit->text().isEmpty())
                {
                    if(!salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getlastname().startsWith(lastnameContainsEdit->text()) && E[i].getage()==(ageContainsEdit->text().toInt())&&E[i].getsalary()==(salaryContainsEdit->text().toInt()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                    if(salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getlastname().startsWith(lastnameContainsEdit->text()) && E[i].getage()==(ageContainsEdit->text().toInt()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                }
                if(ageContainsEdit->text().isEmpty())
                {
                    if(!salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getlastname().startsWith(lastnameContainsEdit->text())&&E[i].getsalary()==(salaryContainsEdit->text().toInt()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                    if(salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getlastname().startsWith(lastnameContainsEdit->text()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                }
            }
            if(lastnameContainsEdit->text().isEmpty())
            {
                if(!ageContainsEdit->text().isEmpty())
                {
                    if(!salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getage()==(ageContainsEdit->text().toInt())&&E[i].getsalary()==(salaryContainsEdit->text().toInt()))
                        {
                             htmlText+="<ol>"+E[i].toString()+"</ol>";
                             found=true;
                        }
                    }
                    if(salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getage()==(ageContainsEdit->text().toInt()))
                        {
                            htmlText+="<ol>"+E[i].toString()+"</ol>";
                            found=true;
                        }
                    }
                }
                if(ageContainsEdit->text().isEmpty())
                {
                    if(!salaryContainsEdit->text().isEmpty())
                    {
                        if(E[i].getsalary()==(salaryContainsEdit->text().toInt()))
                            {
                                htmlText+="<ol>"+E[i].toString()+"</ol>";
                                found=true;
                            }
                    }
                 }
            }
        }
    }
    htmlText+="</ol>";
    if(found==false)
    {
        htmlText="Employee not found";
    }
    QMessageBox::information(this,"Results",htmlText);
    clearSearchSlot();
}

void    MainWindow::clearSearchSlot()
{
    idContainsEdit->setText("");
    nameContainsEdit->setText("");
    lastnameContainsEdit->setText("");
    ageContainsEdit->setText("");
    salaryContainsEdit->setText("");
}

void    MainWindow::reloadTable()
{
    if(mydb==nullptr) return;
    QVector<Employee> e=mydb->employees();
    table->clearContents();
    table->setRowCount(e.size());
    for(int i=0;i<e.size();i++)
    {
        Employee et=e[i];
        table->setItem(i,0,new QTableWidgetItem(QString::number(et.getid())));

        QLineEdit *tableName=new QLineEdit;
        tableName->setText(et.getname());
        table->setCellWidget(i,1,tableName);

        QLineEdit *tableLastName=new QLineEdit;
        tableLastName->setText(et.getlastname());
        table->setCellWidget(i,2,tableLastName);

        QLineEdit *tableAge=new QLineEdit;
        tableAge->setText(QString::number(et.getage()));
        table->setCellWidget(i,3,tableAge);

        QLineEdit *tableSalary=new QLineEdit;
        tableSalary->setText(QString::number(et.getsalary()));
        table->setCellWidget(i,4,tableSalary);

        QPushButton *updateButton=new QPushButton;
        updateButton->setText("UPDATE");
        connect(updateButton,SIGNAL(clicked(bool)),this,SLOT(updateSlot()));

        QPushButton *deleteButton=new QPushButton;
        deleteButton->setText("DELETE");
        connect(deleteButton,SIGNAL(clicked(bool)),this,SLOT(deleteSlot()));
        deleteButton->setProperty("ID",et.getid());
        table->setCellWidget(i,5,deleteButton);
    }
}

void    MainWindow::updateSlot()
{
    QVector<Employee> E=mydb->employees();
    for(int i=0;i<E.size();i++)
    {
    int id=table->item(i,0)->text().toInt();
    QLineEdit *tableName=qobject_cast<QLineEdit *>(table->cellWidget(i,1));
    QLineEdit *tableLastName=qobject_cast<QLineEdit *>(table->cellWidget(i,2));
    QLineEdit *tableAge=qobject_cast<QLineEdit *>(table->cellWidget(i,3));
    QLineEdit *tableSalary=qobject_cast<QLineEdit *>(table->cellWidget(i,4));
    Employee E(id,tableName->text(),tableLastName->text(),tableAge->text().toInt(),tableSalary->text().toInt());
    mydb->updateEmployee(id,E);
    }
    QMessageBox::information(this,"Employee","Database updated");
    reloadTable();
}
void    MainWindow::deleteSlot()
{
    QPushButton *b=qobject_cast<QPushButton *>(sender());
    int id=b->property("ID").toInt();
    mydb->deleteEmployee(id);
    QMessageBox::information(this,"Employee","Employee deleted");
    reloadTable();
}

void    MainWindow::fileSlot(QAction *action)
{
    if(action->text()=="RANDOM")
    {
        QString filename = QFileDialog::getSaveFileName(
                        this, "Write file",
                        ".","db file (*.db)");
            if(filename.size()!=0)
            {
             if(mydb==nullptr) mydb=new Database;
             mydb->setName(filename);
            }
            for(int r=0;r<1000;r++)
            {
                Employee R(r*r+999999+qrand(),GetRandomName(),GetRandomLastName(),18+qrand()%42,400+qrand()%4600);
                mydb->insertEmployee(R);
            }
    }
   else
   if(action->text()=="LOAD")
   {
       QString filename = QFileDialog::getOpenFileName(
                       this, "Open File",
                       ".","db file (*.db)");
           if(filename.size()!=0)
           {
               if(mydb==nullptr)
                   mydb=new Database;
               mydb->setName(filename);
               reloadTable();
           }
   }
   else
   if(action->text()=="SAVE")
   {
       QString filename = QFileDialog::getSaveFileName(
                       this, "Write file",
                       ".","db file (*.db)");
           if(filename.size()!=0)
           {
            if(mydb==nullptr) mydb=new Database;
            mydb->setName(filename);
           }
   }
   else
   if(action->text()=="EXPORT")
   {
        if(mydb==nullptr)
        {
            QMessageBox::critical(this,"Error","Database not opened");
            return;
        }
        QString filename = QFileDialog::getSaveFileName(
                        this, "Write file",
                        ".","csv file (*.txt *.csv)");
            if(filename.size()!=0)
            {
                QVector<Employee> E=mydb->employees();
                QFile file(filename);
                if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QMessageBox::critical(this,"Error","File not opened");
                    return;
                }
                QTextStream st(&file);
                for(int i=0;i<E.size();i++)
                {
                    Employee et=E[i];
                    st<<et.toString()<<endl;
                }
                file.close();
            }

   }
   else
   if(action->text()=="EXIT")
       qApp->exit(0);
}

void    MainWindow::editSlot(QAction *action)
{
    if(action->text()=="NEW")
    {
        panel->setCurrentIndex(0);
    }
    else
    if(action->text()=="DISPLAY")
    {
        panel->setCurrentIndex(1);
    }
    else
    if(action->text()=="SEARCH")
    {
        panel->setCurrentIndex(2);
    }
}
