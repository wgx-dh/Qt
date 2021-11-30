#ifndef RANDIMAGE_H
#define RANDIMAGE_H

#include <QMainWindow>
#include <QImage>
#include <QVector>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QDir>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class RandImage; }
QT_END_NAMESPACE

class RandImage : public QMainWindow
{
    Q_OBJECT

public:
    RandImage(QWidget *parent = nullptr);
    ~RandImage();

private slots:
    void on_pushButton_clicked();

private:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void loadImages(const QString& path);

private:
    Ui::RandImage *ui;
    int m_index;
    int m_timer; // 定时器 ID
    QVector<QImage> m_vecImgList;
    bool m_isActive;
    QString m_path;


};
#endif // RANDIMAGE_H
