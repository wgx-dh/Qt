#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDebug>
#include <QTimer>



QT_BEGIN_NAMESPACE
namespace Ui { class ChatServer; }
QT_END_NAMESPACE

class ChatServer : public QMainWindow
{
    Q_OBJECT

public:
    ChatServer(QWidget *parent = nullptr);
    ~ChatServer();

private slots:
    void on_pushButton_clicked();
    void onNewConnection();
    void onReadyRead();
    void onTimeout();
    void sendMsg(const QByteArray& buf);

private:
    Ui::ChatServer *ui;
    bool status;
    QTcpServer tcpServer;
    QTcpSocket* tcpSocket;
    QVector<QTcpSocket*> tcpSocketList;
    QTimer timer;
};
#endif // CHATSERVER_H
