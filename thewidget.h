#ifndef THEWIDGET_H
#define THEWIDGET_H

#include <QWidget>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QPaintEvent>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QColor>
#include <QImage>
#include <QPen>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QFont>
#include <QKeyEvent>
#include <QIcon>
#include <QVBoxLayout>
#include <QDir>
#include <QLineEdit>
#include <QObject>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QPropertyAnimation>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class theWidget; }
QT_END_NAMESPACE

class theWidget : public QWidget
{
    Q_OBJECT

public:
    theWidget(QWidget *parent = nullptr);
    ~theWidget();

private slots:
    void on_btn_wallpaper_clicked();

    void on_btn_add_clicked();

    void create_unit();

    void sender_name();

    void on_btn_page_clicked();

    void on_btn_page2_clicked();

    void sender_name_unit();

    void on_btn_start_clicked();

    void enterword();

    void on_btn_phone_clicked();

    void on_btn_voice_clicked();

    void on_btn_page3_clicked();

    void on_btn_pageback_clicked();

    void on_btn_en_show_clicked();

    void on_btn_test_clicked();

    void on_btn_next_clicked();

    void chart_update();

    void on_btn_make_clicked();

    void on_btn_return_main_clicked();

    void on_btn_nextword_clicked();

    void on_btn_save_clicked();

    void on_btn_lastword_clicked();

    void on_btn_in_clicked();

    void on_btn_login_clicked();

protected:
    void paintEvent(QPaintEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::theWidget *ui;
    bool winsize = false;
    QString wallpaper;//壁纸的地址。

    QString newcard[201];//新添加的单词卡的地址。
    QVBoxLayout * cardlayout;//单词卡的布局管理器。
    QPushButton * btn_card[201];//单词卡的按钮数组。  
    int card_i = 0;//单词卡个数计数器。

    QGridLayout * unitlayout;//章节的布局管理器。
    int sum_unit,more_unit_num;//章节的个数。
    QPushButton * btn_unit[4001];//单词卡的按钮数组。
    int nSize;//json数组的大小。
    QString unitword[4001];
    QString unittrans[4001][10];
    QString usphone[4001];
    QString ukphone[4001];
    int unit_i = 0;//选择的单元是哪一个。

    int the_card_i;//当前的card_i是哪一个。
    int card_i_btn = 0;//当前按钮对应的数字。
    QString filebasename[201];//文件名，显示在按钮上。

    bool mainwin = true;//判断是否在主页面上。
    int word_i = 0;//记录单词的角标，这个变量的数量等于unit_i * 20。
    int next_word_i = 0;
    int right_sum;//单词正确的个数。
    double right_ratio = 0.0;//正确率。

    bool phone_switch = false;//音标是否打开
    QTimer * tm;//计时器
    int s,m;//分数，秒数。

    //播放器和播放列表。
    QMediaPlayer * player = nullptr;
    QMediaPlaylist * playlist = nullptr;

    //info文件夹中文件的总数。
    int info_sum = 0;
    int data_sum = 1;
    //其中的文件名。
    QStringList info_name;
    QStringList data_name;
    //判断添加文件是手动点击还是自动检测的。
    bool add_ok =false;
    //记录自动添加文件的文件名。
    QString auto_file_name;
    QDir * edir;
    QString current_date;

    //需要储存的数据。
    int data_right_sum = 0;
    int data_all_sum = 0;
    double data_right_ratio = 0.0;

    //壁纸的名字。
    QString auto_wall_name;
    bool wall_ok = false;

    //样式表用的计时器。
    QTimer * tm2;
    int tm2_x = 0;

    //判断英语显示是否打开。
    bool en_show = false;
    bool start_ok = false;

    //用于判断数据库中最大的id。
    int max_i = 0;
    QString sqldata;
    //数据库
    QSqlQuery * sqlQuery;
    int ani_i = 40;
    int ibtn = 0;
    int x[4],y[4];

    int mouth_all_sum = 0;
    int mouth_day = 0;
    int total_sum = 0;
    int total_day = 0;
    int total_right = 0;
    double total_ratio = 0.0;
    QTimer * btntm;

    //鼠标按键的位置。
    QPoint mousePoint;
    bool mouse_press;

    //图表。
    QLineSeries * series;
    QChart * chart;
    //用于显示最近10次的数据。
    int chart_i = 10;
    QCategoryAxis * axisX;

    //新建的单词卡的数据储存。
    int new_word_card_i = 0;
    QString new_filename_str;
    QString new_word[4001];
    QString new_trans[4001];
    QString new_usphone[4001];
    QString new_ukphone[4001];

    QString datauser;
    QString datapassword;

};
#endif // THEWIDGET_H
