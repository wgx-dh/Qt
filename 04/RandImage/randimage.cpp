#include "randimage.h"
#include "ui_randimage.h"

RandImage::RandImage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RandImage)
{
    ui->setupUi(this);
    this->m_index = 0;
    this->m_path = "E:/Code/Qt/06/img";
    this->m_isActive = false;
    this->loadImages(this->m_path);
    qsrand(uint(QTime::currentTime().msec()));

    qDebug() << this->m_vecImgList.size();



}

RandImage::~RandImage()
{
    delete ui;
}

void RandImage::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QRect rect = ui->frame->rect();
    rect.translate(ui->frame->pos());

    painter.drawImage(rect,m_vecImgList.at(m_index));


}
void RandImage::timerEvent(QTimerEvent *){
    m_index = qrand() % m_vecImgList.size();
    update();
}
void RandImage::loadImages(const QString& path){
    QDir dir(path,"",QDir::NoSort,QDir::Files);
    if(dir.entryList().size() > 0){
        for(int i = 0;i < dir.entryList().size();i++){
            QImage img(path+"/"+dir.entryList().at(i));
            this->m_vecImgList.append(img);
        }
    }
//    qDebug() << this->m_vecImgList.size();
    QDir dir2(path,"",QDir::NoSort,QDir::Dirs|QDir::NoDotAndDotDot);
    for(int i = 0; i < dir2.entryList().size();i++){
        qDebug() << path+dir2.entryList().at(i);
        this->loadImages(path+"/"+dir2.entryList().at(i));
    }
}


void RandImage::on_pushButton_clicked()
{
    if(m_isActive == false){
        m_isActive = true;
        ui->pushButton->setText(QStringLiteral("结束"));
        m_timer = startTimer(50);

    }
    else{
        m_isActive = false;
        ui->pushButton->setText(QStringLiteral("开始"));
        killTimer(m_timer);
    }


}
