#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QLineEdit>
# include <QIntValidator>
# include <QPushButton>
# include <QMenu>
# include <QAction>
# include <QStackedLayout>
# include <QTableWidget>
# include <QMessageBox>
# include <QFile>
# include <QTextStream>
# include <QFileDialog>
#include <QRandomGenerator>
# include "database.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QMenu *fileMenu,*editMenu;
    QStackedLayout *panel;
    QTableWidget *table;
    QLineEdit *idEdit,*nameEdit,*lastnameEdit,*ageEdit,*salaryEdit,*deleteButton;
    QLineEdit *idContainsEdit,*nameContainsEdit,*lastnameContainsEdit,*ageContainsEdit,*salaryContainsEdit;
    QPushButton *searchButton;
    QPushButton *addButton;
    QPushButton *updateButton;
    Database *mydb;

    void    makeMenus();
    void    makeDisplayForm();
    void    makeInputForm();
    void    makeSearchForm();
    void    reloadTable();
public slots:
    void fileSlot(QAction *action);
    void editSlot(QAction *action);
    void    addSlot();
    void    clearSlot();
    void    updateSlot();
    void    deleteSlot();
    void    searchSlot();
    void    clearSearchSlot();
    //QString GetRandomString();
};

#endif // MAINWINDOW_H
