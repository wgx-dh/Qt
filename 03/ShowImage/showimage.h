#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>


QT_BEGIN_NAMESPACE
namespace Ui { class ShowImage; }
QT_END_NAMESPACE

class ShowImage : public QMainWindow
{
    Q_OBJECT

public:
    ShowImage(QWidget *parent = nullptr);
    ~ShowImage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ShowImage *ui;
    int m_index;
    void paintEvent(QPaintEvent* );
};
#endif // SHOWIMAGE_H
