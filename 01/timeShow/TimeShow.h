#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTime>

class TimeShow : public QMainWindow
{
    Q_OBJECT
public slots:
    void showTime();
public:
    TimeShow();
    ~TimeShow();
private:
    QLabel* m_label;
    QPushButton* m_button;
    QWidget* m_widget;
    QVBoxLayout* m_layout;
};
#endif // MAINWINDOW_H
