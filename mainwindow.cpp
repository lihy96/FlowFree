#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QString>
#include <QFile>
#include <string>
#include <QColor>
#include <QKeyEvent>
#include <QMessageBox>

#include <QPalette>

#define COLORNUM 7

#define FORWARD 1
#define LEAK 2

#define TASK5 4
#define TASK6 4
#define TASK7 4

#define RED QColor(255,0,0)
#define BLACK Qt::black
#define YELLOW QColor(255,255,0)
#define BLUE QColor(0,0,255)
#define GREEN QColor(0,255,0)
#define ORANGE QColor(245, 178, 0,255)
#define QING QColor(0,255,255,255)
#define ZI QColor(160,32,240,255)

#define LIGHT 150
#define LIRED QColor(255,0,0,LIGHT)
#define LIBLACK Qt::black
#define LIYELLOW QColor(255,255,0,LIGHT)
#define LIBLUE QColor(0,0,255,LIGHT)
#define LIGREEN QColor(0,255,0,LIGHT)
#define LIORANGE QColor(245, 178, 0,LIGHT)
#define LIQING QColor(0,255,255,LIGHT)
#define LIZI QColor(160,32,240,LIGHT)

#define MOVE 1
#define PRESS 2
#define RELEASE 3
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->pushButtonNoUse->hide();
    //设置可以自动填充背景色
      ui->pushButtonNoUse->setAutoFillBackground(true);
      ui->pushButtonNoUse->setStyleSheet("background-color: rgb(255,255,255)");
      //设置背景色为Palette::Shadow
      //ui->pushButtonNoUse->setBackgroundRole(QPalette::Light);

    //
    number = 5;
    isBegin = false;isMouseMove = false;
    task[5] = task[6] = task[7] = 1;
    all[5] = TASK5;
    all[6] = TASK6;
    all[7] = TASK7;
    first.setX(interval+(len/number)/2);
    first.setY(interval+(len/number)/2);
    load(number,task[number]);


    this->setFixedSize(this->width(),this->height ());
    center.setX(width()/2);
    center.setY(width()/2);

    len = 420;
    interval = (width()-len)/2;
    //qDebug()<<interval;

    //设置事件处理器
    //installEventFilter(this);

    mouseX = mouseY = 0;sheerR = 0;//设置半透明图形的圆心和半径

    mouseMode = 0;

    intToColor();//建立int到color的映射

    for(int i = 0;i < 10;i++) finished[i] = 0;

    canVoice = 0;//不播放音乐
    //forward = new QSound("./music/forward.wav");
    //leak = new QSound("./music/leak.wav");
    forward = new QSound(":/music/music/forward.wav");
    leak = new QSound(":/music/music/leak.wav");
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action5_X_5_triggered()
{
    isBegin = true;
    ui->pushButtonNoUse->hide();
    start5();
    first.setX(interval+(len/number)/2);
    first.setY(interval+(len/number)/2);
    //qDebug()<<interval+(len/number)/2;
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
}
void MainWindow::on_action6_X_6_triggered()
{
    isBegin = true;
    ui->pushButtonNoUse->hide();
    start6();
    first.setX(interval+(len/number)/2);
    first.setY(interval+(len/number)/2);
    //qDebug()<<interval+(len/number)/2;
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
}
void MainWindow::on_action7_X_7_triggered()
{
    isBegin = true;
    ui->pushButtonNoUse->hide();
    start7();
    first.setX(interval+(len/number)/2);
    first.setY(interval+(len/number)/2);
    //qDebug()<<interval+(len/number)/2;
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
}
void MainWindow::start5(){
    number = 5;
    load(number,task[number]);
    clearallvc();
    update();
}
void MainWindow::start6(){
    number = 6;
    load(number,task[number]);
    clearallvc();
    update();
}
void MainWindow::start7(){
    number = 7;
    load(number,task[number]);
    clearallvc();
    update();
}
void MainWindow::paintEvent(QPaintEvent *){
    //qDebug() << "PAINTEVEVT" ;
    if(!isBegin) return;
    if(!(number==5||number==6||number==7))
        return ;//之后可以从这里设置一个label提示选择关卡

    QPainter p(this);
    p.setPen(Qt::white);
    p.setBrush(Qt::black);

    p.drawRect(interval,interval,len,len);

    //开始画网格
    for(int i = 0;i <= (len+1);i += len/number){
         p.drawLine(i+interval,interval,i+interval,len+interval);
         p.drawLine(interval,i+interval,len+interval,i+interval);
    }
    //结束画网格

    p.setPen(Qt::black);

    //开始画点
    for(int i = 0;i < number*number;i++){//通过这个来定位网格内的中心点，从而实现添加彩色圆
        int x = i/number;int y = i%number;
        if(!use[x][y]) continue;

        p.setBrush(BLACK);
        if(use[x][y]==1){
            p.setBrush(RED);
        }
        else if(use[x][y]==2){
            p.setBrush(YELLOW);
        }
        else if(use[x][y]==3){
            p.setBrush(GREEN);
        }
        else if(use[x][y]==4){
            p.setBrush(BLUE);
        }
        else if(use[x][y]==5){
            p.setBrush(ORANGE); //画橙色
        }
        else if(use[x][y]==6){
            p.setBrush(QING);//画青色
        }
        else if(use[x][y]==7){
            p.setBrush(ZI);//画紫色
        }
        else
            qDebug() << "ERROR!";

        int r = 0.58*(len/number);
        p.drawEllipse(findposX(y)-r/2,findposY(x)-r/2,r,r);

    }
    //画点结束

    //鼠标移动时开始画圆
    if(isMouseMove && currentColor){
        //int x = findX(mouseY);
        //int y = findY(mouseX);
       // if()
        load(number,task[number]);
        p.setBrush(mouseColor);
        sheerR = len/number*0.9;
        if(use[pressX][pressY])
            p.drawEllipse(mouseX-sheerR/2,mouseY-sheerR/2,sheerR,sheerR);
        else if(currentColor && use[pressX][pressY]==0){//如果是线路的末尾
            intToColor(100);
            p.setBrush(color[currentColor]);
            intToColor(255);
            p.drawEllipse(mouseX-sheerR/2,mouseY-sheerR/2,sheerR,sheerR);
        }

    }
    //画透明圆结束

    //开始画之前记录的线
    for(int k = 1;k <= COLORNUM;k++){
        if(vcx[k].empty()) continue;
        QPen pen(color[k],20,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);

        intToColor(LIGHT-60);//阴影笔
        QPen penShadow(color[k],len/number,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin);
        intToColor(255);

        p.setPen(pen);
        for(int i = 0;i < static_cast<int>(vcx[k].size() - 1);i++){
            int x1 = findposX(vcy[k][i]);
            int y1 = findposY(vcx[k][i]);
            int x2 = findposX(vcy[k][i+1]);
            int y2 = findposY(vcx[k][i+1]);
            p.drawLine(x1,y1,x2,y2);

            //开始画阴影线
            p.setPen(penShadow);
            p.drawLine(x1,y1,x2,y2);
            p.setPen(pen);
            //结束画阴影线
        }
    }
    //结束画之前记录的线

    //开始划鼠标线
    if(isMouseMove||mouseMode==RELEASE){//如果是鼠标按下或者移动的状态
        //int colornow = use[pressX][pressY];
        int colornow = currentColor;
        if(colornow && vcx[colornow].size() > 0
                ){//如果颜色不是黑色
            QPen pen(color[colornow],20,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
            p.setPen(pen);

            for(int i = 0;i < static_cast<int>(vcx[colornow].size() - 1);i++){
                int x1 = findposX(vcy[colornow][i]);
                int y1 = findposY(vcx[colornow][i]);
                int x2 = findposX(vcy[colornow][i+1]);
                int y2 = findposY(vcx[colornow][i+1]);
                p.drawLine(x1,y1,x2,y2);
            }
        }
    }
    //结束划鼠标线


}


void MainWindow::load(int num, int tas){
    for(int i = 0;i < 10;i++)
        for(int j = 0;j < 10;j++)
            use[i][j] = 0;

    //QString path = "./"+QString::number(num)+"_"+QString::number(tas)+".txt";
    //QString path = QString::number(num)+"_"+QString::number(tas)+".txt";
    QString path = ":/text/text/"+QString::number(num)+"_"+QString::number(tas)+".txt";
    qDebug() << path;
    QFile *file=new QFile(path);
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    QString data = QString(file->readAll());
    std::string str = data.toStdString();

    for(int i = 0;i < number*number;i++){
        int x = i/number;
        int y = i%number;
        use[x][y] = str[i]-'0';
    }
}

int MainWindow::findposY(int x){
    return (x*len/number+first.x());
}
int MainWindow::findposX(int y){
    return (y*len/number+first.y());
}
int MainWindow::findX(int y){
    float tmp = (y-first.y())*1.0/(len/number);
    return (int)(tmp+0.5);
}
int MainWindow::findY(int x){
    float tmp = (x-first.x())*1.0/(len/number);
    return (int)(tmp+0.5);
}

void MainWindow::on_nextButton_clicked()
{
    if(!isBegin) return;
    task[number]++;
    if(task[number]>all[number])
        task[number] = 1;
    load(number,task[number]);
    clearallvc();
    update();
    QString str = tr("阶数：")+ QString::number(number) + tr(" ; 关卡数：")+ QString::number(task[number]);
    statusBar()->showMessage (str);//显示临时信息

}

void MainWindow::on_preButton_clicked()
{
    if(!isBegin) return;
    task[number]--;
    if(task[number] < 1)
        task[number] = all[number];
    load(number,task[number]);
    clearallvc();
    update();
    QString str = tr("阶数：")+ QString::number(number) + tr(" ; 关卡数：")+ QString::number(task[number]);
    statusBar()->showMessage (str);//显示临时信息
}

void MainWindow::on_restartButton_clicked()
{
    if(!isBegin) return;
    load(number,task[number]);
    clearallvc();
    update();
}


int MainWindow::colorToInt(QColor c){
    for(int i = 1;i <= COLORNUM;i++){
       if(color[i]==c)
           return i;
    }
    qDebug() << "colorTOInt ERROR";
    return 0;
}

void MainWindow::intToColor(int n){
  color[0] = QColor(0,0,0,0);
  color[1] = QColor(255,0,0,n);//红
  color[2] = QColor(255,255,0,n);//黄
  color[3] = QColor(0,255,0,n);//绿
  color[4] = QColor(0,0,255,n);//蓝
  color[5] = QColor(245,178,0,n);//橙
  color[6] = QColor(0,255,255,n);//青
  color[7] = QColor(160,32,240,n);//紫
}

//********************************************************************************
//鼠标事件*************************************************************************
void MainWindow::mouseMoveEvent ( QMouseEvent * e ){//鼠标移动
   // if(e->button()!= Qt::LeftButton)
     //   return;
    if(e->x() < 40 ||
       e->x() > 460||
       e->y() < 40 ||
       e->y() > 460)
        return;

    mouseMode = MOVE;

    mouseX = e->x();mouseY = e->y();

    isMouseMove = true;

    int x = findX(mouseY);
    int y = findY(mouseX);


    int nowColor = use[pressX][pressY];
    //int nowColor = currentColor;
    //对于黑色的直接清除
    //int judge = judgeTail(0,x,y);
    if(nowColor==0 && currentColor == 0){//如果这里是黑色，而且没有线路尾端
        //qDebug() << "hei" << judge << currentColor;
        vcx[0].clear();
        vcy[0].clear();
    }
    else if(nowColor!=0&&(!use[x][y]||nowColor == use[x][y])){//路线上要跨过彩色点 或者 已经到达目标点

        bool judgex = (x - vcx[nowColor][vcx[nowColor].size()-1]==0)&&
                        (abs(y - vcy[nowColor][vcy[nowColor].size()-1])==1);
        bool judgey = (y - vcy[nowColor][vcy[nowColor].size()-1]==0)&&
                        (abs(x - vcx[nowColor][vcx[nowColor].size()-1])==1);

        qDebug() << "!!" << x << y;
        if((judgex || judgey)  ){//去掉重复结点

            if(x == vcx[nowColor][vcx[nowColor].size()-2] &&//在完成之后也要能返回
               y == vcy[nowColor][vcy[nowColor].size()-2]){
                //qDebug() << "hahahahah";
                vcx[nowColor].pop_back();
                vcy[nowColor].pop_back();
                finished[nowColor] = 0;
            }

            if(!finished[nowColor] && inRange(number,x,y)) {
                vcx[nowColor].push_back(x);
                vcy[nowColor].push_back(y);
            }
            if(arrive(nowColor,x,y)){
                finished[nowColor] = 1;
            }


            //判断重复开始,达到去除环路的目的
            std::vector<int>::iterator itx;
            std::vector<int>::iterator ity;
            for(itx = vcx[nowColor].begin(),ity = vcy[nowColor].begin();
                itx != vcx[nowColor].end(); itx++,ity++){

                if(*itx==x&&*ity==y){//如果发现重复元素
                    itx++;ity++;
                    vcx[nowColor].erase(itx,vcx[nowColor].end());
                    vcy[nowColor].erase(ity,vcy[nowColor].end());
                    break;
                }
            }//判重结束

            //delCross(nowColor,x,y);//这是个bug，会导致一个颜色连接完成之后，移动鼠标仍会打散其他路线
            delCross(nowColor,vcx[nowColor][vcx[nowColor].size()-1],vcy[nowColor][vcy[nowColor].size()-1]);

        }
    }
    else if((currentColor && !use[x][y]) || (currentColor && currentColor==use[x][y])) {


        bool judgex = (x - vcx[currentColor][vcx[currentColor].size()-1]==0)&&
                        (abs(y - vcy[currentColor][vcy[currentColor].size()-1])==1);
        bool judgey = (y - vcy[currentColor][vcy[currentColor].size()-1]==0)&&
                        (abs(x - vcx[currentColor][vcx[currentColor].size()-1])==1);
        qDebug() << judgex << judgey;
        if(judgex || judgey ){//去掉重复结点
            if(x == vcx[currentColor][vcx[currentColor].size()-2] &&//在完成之后也要能返回
               y == vcy[currentColor][vcy[currentColor].size()-2]){

                vcx[currentColor].pop_back();
                vcy[currentColor].pop_back();
                finished[currentColor] = 0;
            }

            //这个if语句中凡是加入//的都需要重写

            if(!finished[currentColor] && inRange(number,x,y)) {

                vcx[currentColor].push_back(x);
                vcy[currentColor].push_back(y);
            }
            if(anoarrive(currentColor,x,y)){
                qDebug() <<"arrive ";
               finished[currentColor] = 1;
            }


           //判断重复开始,达到去除环路的目的
            std::vector<int>::iterator itx;
            std::vector<int>::iterator ity;
            for(itx = vcx[currentColor].begin(),ity = vcy[currentColor].begin();
                itx != vcx[currentColor].end(); itx++,ity++){

                if(*itx==x&&*ity==y){//如果发现重复元素
                    itx++;ity++;
                    vcx[currentColor].erase(itx,vcx[currentColor].end());
                    vcy[currentColor].erase(ity,vcy[currentColor].end());
                    break;
                }
            }//判重结束


           // anodelCross(currentColor,x,y);//这是个bug，会导致一个颜色连接完成之后，移动鼠标仍会打散其他路线
            anodelCross(currentColor,vcx[currentColor][vcx[currentColor].size()-1],vcy[currentColor][vcy[currentColor].size()-1]);
        }
    }
    else{
        qDebug()<< "BIG error";
        vcx[0].clear();
        vcy[0].clear();
    }

    //结束
    update();
    //repaint();
}
int firstt = 0;
void MainWindow::mousePressEvent ( QMouseEvent * e ){//鼠标按下
   /* if(e->button()!= Qt::LeftButton)
        return;
    if(e->x() < interval ||
       e->x() > len + interval||
       e->y() < interval ||
       e->y() > len + interval)
        return;*/

    mouseMode = PRESS;

   // if(!isBegin) return;
    mouseX = e->x();mouseY = e->y();

    isMouseMove = true;

    int x = findX(mouseY);
    int y = findY(mouseX);


        pressX = x;//用来记录鼠标最初按下的坐标
        pressY = y;
        if(use[x][y]){
            anopressX = x;
            anopressY = y;
        }

    currentColor = use[x][y];
    if(judgeTail(currentColor,x,y) && currentColor == 0){//currentcolor==0 是说当前确实是从尾巴出的
        currentColor = judgeTail(currentColor,x,y);
    }

    intToColor(100);
    mouseColor = color[use[x][y]];
    intToColor(255);

    //按下鼠标之后记录
    int nowColor = use[pressX][pressY];
    if(nowColor&& inRange(number,x,y)){
        vcx[nowColor].clear();
        vcy[nowColor].clear();
        vcx[nowColor].push_back(x);
        vcy[nowColor].push_back(y);
    }//记录结束


    jugeMiddle(0,x,y);//如果按下线路中间的某个按键，则从此中断

    repaint();
    isMouseMove = false;
}
void MainWindow::mouseReleaseEvent ( QMouseEvent *  ){//鼠标释放


    mouseMode = RELEASE;
    for(int i = 0;i < 10;i++) finished[i] = 0;
    isMouseMove = false;



    //permit = true;
    if(canVoice){
        if(canVoice==LEAK)
            leak->play();
        else if(canVoice==FORWARD)
            forward->play();

        canVoice = 0;
    }
    if(isFinish()) afterFinish();
    //permit = false;

    repaint();
}
void MainWindow::mouseDoubleClickEvent( QMouseEvent *  ){//鼠标双击
    //nothing
   return;
}

int MainWindow::delCross(int ,int x,int y){//判断x，y这个点是否已经有
    //注：此处color并没有作用，因为可以通过pressX代替color
    std::vector<int>::iterator itx;
    std::vector<int>::iterator ity;
    for(int i = 1;i <= COLORNUM;i++){
       if(i==use[pressX][pressY])// 对于自己的颜色不进行相交判断
           continue;
       for(itx = vcx[i].begin(),ity = vcy[i].begin();
           itx != vcx[i].end(); itx++,ity++){
           if(*itx == x && *ity == y){

               //播放音乐
               //QSound::play("../bigProject/leak.wav");
               canVoice = LEAK;
               //leak->play();
                while(1){
                    int tmpx = vcx[i][vcx[i].size()-1];
                    int tmpy = vcy[i][vcy[i].size()-1];
                    vcx[i].pop_back();
                    vcy[i].pop_back();
                    qDebug() << " "<<tmpx << tmpy;
                    if(tmpx == x && tmpy == y)
                        return 1;
                }
           }

       }
    }
    return 0;
}

int MainWindow::anodelCross(int , int x, int y)
{
    //注：此处color并没有作用，因为可以通过pressX代替color
    std::vector<int>::iterator itx;
    std::vector<int>::iterator ity;
    for(int i = 1;i <= COLORNUM;i++){
       if(i==currentColor)// 对于自己的颜色不进行相交判断
           continue;
       for(itx = vcx[i].begin(),ity = vcy[i].begin();
           itx != vcx[i].end(); itx++,ity++){
           if(*itx == x && *ity == y){
               //播放音乐
               //QSound::play("../bigProject/leak.wav");
                canVoice = LEAK;

                while(1){
                    int tmpx = vcx[i][vcx[i].size()-1];
                    int tmpy = vcy[i][vcy[i].size()-1];
                    vcx[i].pop_back();
                    vcy[i].pop_back();
                    qDebug() << "Cao "<<tmpx << tmpy;
                    if(tmpx == x && tmpy == y)
                        return 1;
                }
           }

       }
    }
    return 0;
}




void MainWindow::on_actionReturn_triggered()
{
    isBegin = false;
    update();
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();
}
void MainWindow::clearallvc(){
    for(int i = 0;i < 10;i++){
        vcx[i].clear();
        vcy[i].clear();
    }
}


bool MainWindow::isFinish(){

    int tmp[100];
    for(int i = 0;i < 100;i++) tmp[i] = -1;

    for(int i = 1;i <= COLORNUM;i++){
        std::vector<int>::iterator itx;
        std::vector<int>::iterator ity;

        for(itx = vcx[i].begin(),ity = vcy[i].begin();itx != vcx[i].end();itx++,ity++){
            int num = (*itx)*number + (*ity);
            tmp[num] = 1;
            qDebug() << num;
        }
    }
    for(int i = 0;i < number*number;i++){
        if(tmp[i] == -1)
            return false;
    }

    return true;
}


void MainWindow::afterFinish(){
    //qDebug () << "Finish !";
    //if(!permit) return;
    QMessageBox message;
    message.setWindowTitle(tr("恭喜您已完成"));
    message.setText(tr("您太厉害了！     棒棒哒~"));
    message.setModal(true);
    QPushButton* re = message.addButton(tr("重玩"),QMessageBox::ActionRole);
    QPushButton* ne = message.addButton(tr("下一关"),QMessageBox::ActionRole);
    QPushButton* cancel = message.addButton((QMessageBox::Cancel));

    message.exec();
    if(message.clickedButton()==re){
        on_restartButton_clicked();
    }
    else if(message.clickedButton()==ne){
        on_nextButton_clicked();
    }
    else if(message.clickedButton()==cancel){
        //nothing
    }
    else
        qDebug() << "ERROR AFTERFINISH";
}

bool MainWindow::arrive(int ,int x,int y){

    if((!( x==pressX && y==pressY )) && use[x][y] == use[pressX][pressY])
    {
        //播放背景音乐
        //QSound::play("../bigProject/forward.wav");
        canVoice = FORWARD;
        //停止画
        qDebug() << "music";
        //qDebug() << "arrive : " << n;
        //QSound player(":/music/forward.wav");
        //player.play();
        return true;
    }
    return false;
}
bool MainWindow::anoarrive(int ,int x,int y){
    //if((!( x==anopressX && y==anopressY )) && use[x][y] == use[anopressX][anopressY])
    if((!( x==anopressX && y==anopressY )) && use[x][y] == currentColor)
    {
        //播放背景音乐
        //QSound::play("../bigProject/forward.wav");
        canVoice = FORWARD;
        //停止画
        qDebug() << "music";
        //qDebug() << "arrive : " << n;
        //QSound player(":/music/forward.wav");
        //player.play();
        return true;
    }
    return false;
}

int MainWindow::judgeTail(int ,int x,int y){
    for(int i = 1;i <= COLORNUM;i++){
        if(vcx[i].empty())
            continue;
        int tailx = vcx[i][vcx[i].size()-1];
        int taily = vcy[i][vcy[i].size()-1];
        if(tailx == x && taily == y){
            return i;
        }
    }
    return 0;
}
int MainWindow::jugeMiddle(int , int x, int y){
    std::vector<int>::iterator itx;
    std::vector<int>::iterator ity;
    for(int i = 1;i <= COLORNUM;i++){
        if(vcx[i].empty())
            continue;
        for(itx = vcx[i].begin(),ity = vcy[i].begin();
            itx != vcx[i].end(); itx++,ity++){
            if(*itx == x && *ity == y){
                while(1){
                    int tmpx = vcx[i][vcx[i].size()-1];
                    int tmpy = vcy[i][vcy[i].size()-1];
                    if(!(tmpx==x&&tmpy==y)){
                        vcx[i].pop_back();
                        vcy[i].pop_back();
                    }
                    else
                        return i;
                }
            }
        }

    }
    return 0;
}

bool MainWindow::inRange(int n, int x, int y)
{
    return (x>=0 && y>=0 && x<n && y<n);
}

void MainWindow::on_pushButton_clicked()
{
    on_action5_X_5_triggered();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    on_action6_X_6_triggered();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
}

void MainWindow::on_pushButton_3_clicked()
{
    on_action7_X_7_triggered();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
}
void MainWindow::closeEvent(QCloseEvent * event) {
    int ret = QMessageBox::warning(0, tr("MainWindow"), tr("Do you really want to exit?"), QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_pushButtonNoUse_clicked()
{
    if(!isBegin) return;
    qDebug() << "error";
    //update();
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::information(this,tr("更多信息"),tr("<a href='http://www.flowanswers.com/'>更多信息请参考: http://www.flowanswers.com/</a>"));
}

void MainWindow::on_actionNew_Picture_triggered()
{

}
