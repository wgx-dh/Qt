#include "randimage.h"
#include "ui_randimage.h"

RandImage::RandImage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RandImage)
{
    ui->setupUi(this);
    qsrand(uint(QTime::currentTime().msec()));
    m_index = 0;
    m_isActive = false;
    m_path = "E:/Code/Qt/06/img";
    this->loadImages(m_path);
    m_timer = new QTimer(this);

    connect(m_timer,SIGNAL(timeout()),
            this,SLOT(enableUpadate()));
}

RandImage::~RandImage()
{
    delete ui;
}

void RandImage::enableUpadate(){
    m_index = qrand() % this->m_vecImgList.size();
    update();
}

void RandImage::paintEvent(QPaintEvent* ){
    QPainter painter(this);
    QRect rect = ui->frame->rect();
    rect.translate(ui->frame->pos());

    painter.drawImage(rect,this->m_vecImgList.at(m_index));

}

void RandImage::loadImages(const QString& path){
    QDir dir(path,"",QDir::Unsorted,QDir::Files);
    qDebug() << dir.entryList();
    for(int i = 0;i< dir.entryList().size();i++){
        QImage img(path+"/"+dir.entryList().at(i));
        this->m_vecImgList.append(img);
    }

    QDir dir2(path,"",QDir::Unsorted,QDir::Dirs|QDir::NoDotAndDotDot);
    for(int i = 0;i<dir2.entryList().size();i++){
        loadImages(path+"/"+dir2.entryList().at(i));
    }

}

void RandImage::on_pushButton_clicked()
{
    if(m_isActive == false){
        m_isActive = true;
        ui->pushButton->setText(QStringLiteral("结束"));
        m_timer->start(50);
    }
    else{
        m_isActive = false;
        ui->pushButton->setText(QStringLiteral("开始"));
        m_timer->stop();
    }

}
