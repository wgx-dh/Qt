#include "chatserver.h"
#include "ui_chatserver.h"

ChatServer::ChatServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatServer)
{
    ui->setupUi(this);
    status = false;

    connect(&tcpServer,SIGNAL(newConnection()),
            this,SLOT(onNewConnection()));
    connect(&timer,SIGNAL(timeout()),
            this,SLOT(onTimeout()));


}

void ChatServer::onTimeout(){
    for(int i = 0;i<tcpSocketList.size();i++){
        if(!tcpSocketList.at(i)->isValid()){
            tcpSocketList.remove(i);
            i--;
        }
    }
}

void ChatServer::sendMsg(const QByteArray& buf){
    for(int i = 0;i<tcpSocketList.size();i++){
        if(tcpSocketList.at(i)->isValid()){
            tcpSocketList.at(i)->write(buf);
        }
    }
}

void ChatServer::onReadyRead(){
    for(int i = 0;i < tcpSocketList.size();i++){
        if(tcpSocketList.at(i)->bytesAvailable()){
            QByteArray buf = tcpSocketList.at(i)->readAll();
            sendMsg(buf);
            ui->listWidget->addItem(buf);
            ui->listWidget->scrollToBottom();
        }
    }

}

void ChatServer::onNewConnection(){
    QTcpSocket* tcpSocket = tcpServer.nextPendingConnection();
    tcpSocketList.append(tcpSocket);
    connect(tcpSocket,SIGNAL(readyRead()),
            this,SLOT(onReadyRead()));
}

void ChatServer::on_pushButton_clicked()
{
    if(status == false){
        quint16 port = quint16(ui->portEdit->text().toShort());
        if(tcpServer.listen(QHostAddress::Any,port)){
            ui->pushButton->setText(QStringLiteral("关闭服务器"));
            status = true;
            timer.start(3000);
        }
        else{
            qDebug() << QStringLiteral("启动服务器失败！");
        }
    }
    else{
        tcpServer.close();
        timer.stop();
        ui->pushButton->setText(QStringLiteral("启动服务器"));
        status = false;
    }


}




ChatServer::~ChatServer()
{
    delete ui;
}
