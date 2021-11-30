#ifndef RANDIMAGE_H
#define RANDIMAGE_H

#include <QMainWindow>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QDebug>
#include <QImage>
#include <QDir>


QT_BEGIN_NAMESPACE
namespace Ui { class RandImage; }
QT_END_NAMESPACE

class RandImage : public QMainWindow
{
    Q_OBJECT

public:
    RandImage(QWidget *parent = nullptr);
    ~RandImage();
public slots:
    void enableUpadate();
private:
    void paintEvent(QPaintEvent* );
    void loadImages(const QString& path);
private slots:
    void on_pushButton_clicked();

private:
    Ui::RandImage *ui;
    QVector<QImage> m_vecImgList;
    QString m_path;
    QTimer* m_timer;
    bool m_isActive;
    int m_index;
};
#endif // RANDIMAGE_H
