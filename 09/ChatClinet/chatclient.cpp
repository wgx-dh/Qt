#include "chatclient.h"
#include "ui_chatclient.h"

ChatClient::ChatClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatClient)
{
    ui->setupUi(this);
    status = false;
    ui->sentButton->setEnabled(false);
    connect(&tcpSocket,SIGNAL(connected()),
            this,SLOT(onConnected()));
    connect(&tcpSocket,SIGNAL(disconnected()),
            this,SLOT(onDisconnected()));
    connect(&tcpSocket,SIGNAL(readyRead()),
            this,SLOT(onReadyRead()));
    connect(&tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(onError()));
}

ChatClient::~ChatClient()
{
    delete ui;
}

void ChatClient::onConnected(){
    status = true;
    ui->connectButton->setText(QStringLiteral("断开连接"));
    ui->sentButton->setEnabled(true);

    QString msg = name + QStringLiteral(":进入了聊天室");
    tcpSocket.write(msg.toUtf8());
}

void ChatClient::onDisconnected(){

    status = false;
    ui->connectButton->setText((QStringLiteral("连接服务器")));
    ui->sentButton->setEnabled(false);
}

void ChatClient::onReadyRead(){
    if(tcpSocket.bytesAvailable()){
        QByteArray msg = tcpSocket.readAll();
        ui->listWidget->addItem(msg);
        ui->listWidget->scrollToBottom();
    }


}

void ChatClient::onError(){
    QMessageBox::critical(this,"ERROR",tcpSocket.errorString());
}

void ChatClient::on_sentButton_clicked()
{
    QString msg = ui->msgEdit->text();
    if(msg == "") return;
    msg = name + ":" + msg;
    tcpSocket.write(msg.toUtf8());
    ui->msgEdit->clear();
}

void ChatClient::on_connectButton_clicked()
{
    if(status == false){
        serverIP.setAddress(ui->ipEdit->text());
        name = ui->nameEdit->text();
        quint16 port = quint16(ui->portEdit->text().toShort());
        tcpSocket.connectToHost(serverIP,port);

    }
    else{
        QString msg = name + QStringLiteral(":离开了聊天室");
        tcpSocket.write(msg.toUtf8());
        tcpSocket.disconnectFromHost();

    }

}
