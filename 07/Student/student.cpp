#include "student.h"
#include "ui_student.h"

Student::Student(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Student)
{
    ui->setupUi(this);
    this->initMenber();

}

void Student::initMenber(){
    m_db = new QSqlDatabase();
    m_model = new QSqlQueryModel(this);
    *m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db->setDatabaseName("StudentScore.db");

    if(m_db->open()){
        qDebug() << QStringLiteral("数据库创建成功！");
        QSqlQuery query;
        QString str = "CREATE TABLE StudentScore("
                      "id INT PRIMARY KEY NOT NULL,"
                      "name TEXT NOT NULL,"
                      "score REAL NOT NULL);";
        query.exec(str);
        this->showAll();
    }
    else{
        qDebug() << QStringLiteral("数据库创建失败！");
    }
}

void Student::showAll(){

    m_model->setQuery("SELECT * FROM StudentScore");
    ui->tableView->setModel(m_model);
    ui->tableView->show();
}



void Student::on_insertButton_clicked()
{
    QSqlQuery query;

    bool flag = true;
    int id = ui->idEdit->text().toInt(&flag);
    if(!flag){
        QMessageBox::critical(this,"Error",QStringLiteral("输入 id 应为整数！"));
        return;
    }
    QString name = ui->nameEdit->text();
    double score = ui->scoreEdit->text().toDouble(&flag);
    if(!flag || score > 100 || score < 0){
        QMessageBox::critical(this,"Error",QStringLiteral("成绩输入错误！"));
        return;
    }
    QString sql_str = QString("INSERT INTO StudentScore "
                              "VALUES(%1,'%2',%3)").arg(id).arg(name).arg(score);
    if(!query.exec(sql_str)){
        QString err_str = m_db->lastError().text();
        qDebug() << err_str;
        QMessageBox::critical(this,"Error",err_str);
    }

    this->showAll();
}

void Student::on_deleteButton_clicked()
{
    QSqlQuery query;

    bool flag = true;
    int id = ui->idEdit->text().toInt(&flag);
    if(!flag){
        QMessageBox::critical(this,"Error",QStringLiteral("输入 id 应为整数！"));
        return;
    }
    QString sql_str = QString("DELETE FROM StudentScore WHERE id = %1").arg(id);

    if(!query.exec(sql_str)){
        qDebug() << sql_str;
        QString err_str = m_db->lastError().text();
        qDebug() << err_str;
        QMessageBox::critical(this,"Error",err_str);
    }
    else{
        if(QMessageBox::question(this,QString("Delete id = %1").arg(id),
                                 QStringLiteral("确定删除？"),QMessageBox::Yes|QMessageBox::No)
                == QMessageBox::Yes){
            QMessageBox::information(this,"Success",QStringLiteral("删除成功！"));
        }

    }
    this->showAll();
}


void Student::on_sortButton_clicked()
{
    QString condition = (ui->conditionComboBox->currentIndex() == 0?
                             "ASC":"DESC");
    QString val = (ui->valComboBox->currentIndex() == 0?"id":"score");

    QString sql_str = QString("SELECT * FROM StudentScore ORDER BY"
                              " %1 %2").arg(val).arg(condition);
    m_model->setQuery(sql_str);
    ui->tableView->setModel(m_model);
}

Student::~Student()
{
    delete ui;
}

void Student::on_updateButton_clicked()
{
    QSqlQuery query;

    bool flag = true;
    int id = ui->idEdit->text().toInt(&flag);
    if(!flag){
        QMessageBox::critical(this,"Error",QStringLiteral("输入 id 应为整数！"));
        return;
    }
    QString name = ui->nameEdit->text();
    double score = ui->scoreEdit->text().toDouble(&flag);
    if(!flag || score > 100 || score < 0){
        QMessageBox::critical(this,"Error",QStringLiteral("成绩输入错误！"));
        return;
    }

    QString sql_str = QString("UPDATE StudentScore SET name='%1',score=%2 "
                              "WHERE id=%3").arg(name).arg(score).arg(id);
    if(!query.exec(sql_str)){
        qDebug() << sql_str;
        QString err_str = m_db->lastError().text();
        qDebug() << err_str;
        QMessageBox::critical(this,"Error",err_str);
    }
    else{
        QMessageBox::information(this,"Success",QStringLiteral("修改成功！"));
    }
    this->showAll();

}

void Student::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();

    QString id = m_model->data(m_model->index(row,0)).toString();
    QString name = m_model->data(m_model->index(row,1)).toString();
    QString score = m_model->data(m_model->index(row,2)).toString();

    ui->nameEdit->setText(name);
    ui->idEdit->setText(id);
    ui->scoreEdit->setText(score);

}
