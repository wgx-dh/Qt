#include "mouseevent.h"
#include "ui_mouseevent.h"

MouseEvent::MouseEvent(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MouseEvent)
{
    ui->setupUi(this);
    m_moveTag = false;
}

void MouseEvent::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        QRect rect = ui->label->frameRect();
        rect.translate(ui->label->pos());
        if(rect.contains(e->pos())){
            m_moveTag = true;
            m_pos = ui->label->pos() - e->pos();
        }
    }
}
void MouseEvent::mouseReleaseEvent(QMouseEvent *){
    m_moveTag = false;
}
void MouseEvent::mouseMoveEvent(QMouseEvent *e){
    if(m_moveTag){
        QPoint newPos = m_pos + e->pos();
        if(newPos.x() < 0){
            newPos.setX(0);
        }
        newPos.setY(newPos.y()<0?0:newPos.y());
        newPos.setX(newPos.x()>this->width()-ui->label->width()?
                        this->width()-ui->label->width():newPos.x());
        newPos.setY(newPos.y()>this->height()-ui->label->height()?
                        this->height()-ui->label->height():newPos.y());
        ui->label->move(newPos);
    }
}

void MouseEvent::keyPressEvent(QKeyEvent *e){
    QPoint newPos = ui->label->pos();
    if(e->key() == Qt::Key_Up){
        newPos.setY(newPos.y()-5);
    }
    if(e->key() == Qt::Key_Down){
        newPos.setY((newPos.y()+5));
    }
    if(e->key() == Qt::Key_Left){
        newPos.setX(newPos.x()-5);
    }
    if(e->key() == Qt::Key_Right){
        newPos.setX((newPos.x()+5));
    }
    newPos.setX(newPos.x()<0?0:newPos.x());
    newPos.setY(newPos.y()<0?0:newPos.y());
    newPos.setX(newPos.x()>this->width()-ui->label->width()?
                    this->width()-ui->label->width():newPos.x());
    newPos.setY(newPos.y()>this->height()-ui->label->height()?
                    this->height()-ui->label->height():newPos.y());
    ui->label->move(newPos);
}





MouseEvent::~MouseEvent()
{
    delete ui;
}

