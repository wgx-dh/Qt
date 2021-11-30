#include "TimeShow.h"
TimeShow::~TimeShow(){

}
TimeShow::TimeShow(){
    m_widget = new QWidget(this);
    m_label = new QLabel(m_widget);
    m_button = new QPushButton("显示系统时间",m_widget);
    m_layout = new QVBoxLayout(m_widget);
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_button);
    m_widget->setLayout(m_layout);
    this->setCentralWidget(m_widget);
    m_label->setFrameStyle(QFrame::StyledPanel);
    m_label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    QFont font;
    font.setPointSize(20);
    m_button->setFont(font);
    m_label->setFont(font);

    QObject::connect(m_button,SIGNAL(clicked()),
                     this,SLOT(showTime()));
}

void TimeShow::showTime(){
    QString str = QTime::currentTime().toString("hh:mm:ss");
    m_label->setText(str);
}
