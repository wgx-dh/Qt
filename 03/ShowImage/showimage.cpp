#include "showimage.h"
#include "ui_showimage.h"

ShowImage::ShowImage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShowImage)
{
    m_index = 1;
    ui->setupUi(this);
}

ShowImage::~ShowImage()
{
    delete ui;
}

void ShowImage::paintEvent(QPaintEvent *){
    // 创建画家对象
    QPainter painter(this);

    QRect rect = ui->frame->frameRect();
    rect.translate(ui->frame->pos());

    QImage img(":/img/"+QString::number(m_index)+".png");

    painter.drawImage(rect,img);
}

void ShowImage::on_pushButton_clicked()
{
    if(++m_index > 6){
        m_index = 1;
    }
    this->update();
}

void ShowImage::on_pushButton_2_clicked()
{
    if(--m_index < 1){
        m_index = 6;
    }
    this->update();

}
