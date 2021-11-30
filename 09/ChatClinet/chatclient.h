#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QTcpServer>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class ChatClient; }
QT_END_NAMESPACE

class ChatClient : public QMainWindow
{
    Q_OBJECT

public:
    ChatClient(QWidget *parent = nullptr);
    ~ChatClient();

private slots:


    void on_sentButton_clicked();

    void onConnected();

    void onDisconnected();

    void on_connectButton_clicked();

    void onReadyRead();

    void onError();

private:
    Ui::ChatClient *ui;
    QTcpSocket tcpSocket;
    QHostAddress serverIP;
    bool status;
    QString name;
};
#endif // CHATCLIENT_H
