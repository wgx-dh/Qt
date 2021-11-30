#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QDialog>
#include <QMouseEvent>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MouseEvent; }
QT_END_NAMESPACE

class MouseEvent : public QDialog
{
    Q_OBJECT

public:
    MouseEvent(QWidget *parent = nullptr);
    ~MouseEvent();

private:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::MouseEvent *ui;
    bool m_moveTag;
    QPoint m_pos;
};
#endif // MOUSEEVENT_H
