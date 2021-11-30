#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    QObject::connect(ui->m_btn,SIGNAL(accepted()),
                     this,SLOT(onAccept()));
    QObject::connect(ui->m_btn,SIGNAL(rejected()),
                     this,SLOT(onReject()));
}

void Login::onAccept(){
    QMessageBox msg(QMessageBox::Critical,
                    QString::fromUtf8("Error"),
                    QStringLiteral("用户名或密码错误！"),
                    QMessageBox::Ok,
                    this);
    if (ui->m_Edit_1->text() == QString::fromUtf8("wgx") &&
            ui->m_Edit_2->text() == QString::fromUtf8("123456")){
//        qDebug(QString::fromUtf8("111"));
        this->close();
    }
    else{
        msg.exec();
    }
}

void Login::onReject(){
    QMessageBox msg(QMessageBox::Question,
                    QString::fromUtf8("Warning"),
                    QStringLiteral("确定要退出吗？"),
                    QMessageBox::Yes|QMessageBox::No,
                    this);
    if(msg.exec() == QMessageBox::Yes){
        this->close();
    }
}

Login::~Login()
{
    delete ui;
}

