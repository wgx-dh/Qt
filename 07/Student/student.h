#ifndef STUDENT_H
#define STUDENT_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class Student; }
QT_END_NAMESPACE

class Student : public QMainWindow
{
    Q_OBJECT

public:
    Student(QWidget *parent = nullptr);
    ~Student();


public:
    void initMenber();
    void showAll();

private slots:
    void on_insertButton_clicked();

    void on_deleteButton_clicked();

    void on_sortButton_clicked();

    void on_updateButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::Student *ui;
    QSqlDatabase *m_db;
    QSqlQueryModel *m_model;
};
#endif // STUDENT_H
