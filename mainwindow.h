#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPoint>
#include <vector>
#include <QSound>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *ev);
    void start5();
    void start6();
    void start7();

    //bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent ( QMouseEvent * e );//鼠标移动事件
    void mousePressEvent ( QMouseEvent * e );//鼠标按下事件
    void mouseReleaseEvent ( QMouseEvent * e );//鼠标释放的事件
    void mouseDoubleClickEvent( QMouseEvent * e );//鼠标双击的事件*/
    void closeEvent(QCloseEvent * event);

private slots:
    void on_action5_X_5_triggered();

    void on_action6_X_6_triggered();

    void on_action7_X_7_triggered();

    void on_nextButton_clicked();

    void on_preButton_clicked();

    void on_restartButton_clicked();

    void on_actionReturn_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButtonNoUse_clicked();

    void on_pushButton_4_clicked();

    void on_actionNew_Picture_triggered();

private:
    Ui::MainWindow *ui;


    int len;//边长，设定为420
    int gezilen;//记录每个格子的长度
    int number;//记录每条边的格子数目

    int task[10];//记录当前走到了第几关
    int all[10];
    int use[10][10];//用于记录一些信息，比如是否用笔画经过，此处是否有点等等
    int trace[10][10];//用于记录是否有路线经过的二维数组
    //int old[10][10];
    QPoint center;
    QPoint first;
    int interval;//边框的距离
    //bool permit;

    void load(int num,int tas);//重新读取文件从而修改use【】【】

    int findposX(int x);//得到x，y这个位置的中心像素点 横坐标
    int findposY(int y);//得到x，y这个位置的中心像素点 纵坐标
    int findX(int x);//通过像素点得到格子的横坐标
    int findY(int y);

    bool isBegin;//判断游戏是否已经开始

    int mouseX,mouseY;//鼠标的像素坐标
    int sheerR;//代表鼠标移动时显示的小圆圈的半径
    bool isMouseMove;//代表当前事件是否是鼠标
    std::vector<int> vcx[10];
    std::vector<int> vcy[10];
    void clearallvc();

    int colorToInt(QColor c);
    void intToColor(int n = 255);
    QColor color[10];//记录颜色的数组，从而实现数字和颜色的映射

    int mouseMode;//设置当前的鼠标模式，从而在paintevent内加以区分

    QColor mouseColor;//指示当前鼠标的颜色值，用在追随鼠标移动的透明小圆环上

    int pressX,pressY;
    int currentColor;

    bool isFinish();//判断是否完成
   // bool anoisFinish();
    void afterFinish();//在完成之后的相应操作
    //void anoafterFinish();

    bool arrive(int n,int x,int y);
    bool anoarrive(int n,int x,int y);
    int delCross(int color,int x,int y);//处理两条路线香蕉的问题；
    int anodelCross(int n,int x,int y);

    //bool canUseMouse;
    int finished[10];

    int judgeTail(int n,int x,int y);
    int jugeMiddle(int n,int x,int y);

    int anopressX,anopressY;
    bool inRange(int n,int x,int y);//

    QSound *forward,*leak;
    int canVoice;
};

#endif // MAINWINDOW_H
