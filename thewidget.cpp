#include "thewidget.h"
#include "ui_thewidget.h"

theWidget::theWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::theWidget)
{
    ui->setupUi(this);

    //窗口无边框。
    setWindowFlags(Qt::FramelessWindowHint);

    //密文输入。
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);

    //设置提示文字。
    ui->lineEdit_user->setPlaceholderText("input your username");
    ui->lineEdit_pwd->setPlaceholderText("input your password");

    ui->lineEdit_pwd->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->lineEdit_user->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->btn_login->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed



    QPalette pal(this->palette());
    //设置背景色
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    btntm = new QTimer;
    btntm->start(10);

    this->setStyleSheet("QWidget{border-top-left-radius:15px;border-top-right-radius:5px;}");

    //设置字体。Microsoft YaHei Light
    QFont ft("Microsoft YaHei Light",20, 25);
    QFont ftm("Microsoft YaHei Light",12, 25);
    QFont titleft("Microsoft YaHei Light",30, 25);
    ui->label_today_sum->setFont(ft);
    ui->label_today_sum->setAlignment(Qt::AlignHCenter);
    ui->label_rw->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_trans->setAlignment(Qt::AlignHCenter);
    ui->label_phone->setAlignment(Qt::AlignHCenter);
    ui->label_2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_time->setFont(ft);
    ui->label_rw->setFont(ft);
    ui->label_right_sum->setFont(ft);
    ui->label_right_ratio->setFont(ft);
    ui->label->setFont(ft);
    ui->label_2->setFont(titleft);
    ui->label_3->setFont(titleft);
    ui->label_trans->setFont(ft);
    ui->label_phone->setFont(ftm);
    ui->btn_start->setFont(ftm);
    ui->btn_phone->setFont(ftm);
    ui->btn_page2->setFont(ftm);
    ui->btn_page->setFont(ftm);
    ui->btn_pageback->setFont(ftm);
    ui->btn_en_show->setFont(ftm);
    ui->label_4->setFont(titleft);
    ui->label_5->setFont(titleft);
    ui->label_6->setFont(titleft);
    ui->label_7->setFont(titleft);
    ui->label_4->setAlignment(Qt::AlignRight);
    ui->label_6->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->label_9->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_10->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_12->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_11->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->treeWidget->setFont(ftm);
    ui->label_choice->setFont(ft);
    ui->label_login->setFont(titleft);
    ui->label_login->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QFont ftL("Microsoft YaHei Light",20, 25);
    ui->lineEdit->setFont(ftL);
    ui->lineEdit->setAlignment(Qt::AlignHCenter);

    //treeWidget的使用。
    //设置水平头。
    ui->treeWidget->setHeaderLabels(QStringList() << "日期" << "统计");
    //加载顶层的节点。
    QTreeWidgetItem * thisweek = new QTreeWidgetItem(QStringList()<<"每日数据");
    QTreeWidgetItem * lastweek = new QTreeWidgetItem(QStringList()<<"总数据");
    ui->treeWidget->addTopLevelItem(thisweek);
    ui->treeWidget->addTopLevelItem(lastweek);
    ui->treeWidget->header()->resizeSection(0,300);

    //声明播放器。
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;
    player->setVolume(100);
    player->setPlaylist(playlist);

    //计时器。
    tm = new QTimer(this);
    tm2 = new QTimer(this);
    connect(tm2,&QTimer::timeout,[=](){
        tm2_x++;
        if(tm2_x >= player->duration() / 100){
            tm2_x = 0;
            ui->btn_voice->setStyleSheet("QPushButton#btn_voice{border-image:url(:/nakiri/sou/声音-线性.png);}QPushButton#btn_voice:hover{border-image:url(:/nakiri/sou/声音.png);}");
        }
    });
    connect(tm,&QTimer::timeout,[=](){
        s++;
        if(s >= 60){
            s = 0;
            m++;
        }

        QString m0,s0;
        if(s < 10){
            s0 = "0";
        }else{
            s0 = "\0";
        }
        if(m < 10){
            m0 = "0";
        }else{
            m0 = "\0";
        }
        QString time_text = "时间:"+m0+QString::number(m)+":"+s0+QString::number(s);
        ui->label_time->setText(time_text);
    });

    //声明布局器。
    cardlayout = new QVBoxLayout();
    unitlayout = new QGridLayout;

    //单词卡的滚动条。
    ui->scrollArea_card->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//纵向一直打开。
    ui->scrollArea_card->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//横向一直不打开。

    //右上角的三个按键（没有换壁纸的按键）。
    connect(ui->btn_close,&QPushButton::clicked,this,&QWidget::close);
    connect(ui->btn_max,&QPushButton::clicked,[=](){
        if(winsize==true){
            ui->btn_max->setStyleSheet("QPushButton#btn_max{border-image:url(:/nakiri/sou/最大化.png);}");
            setWindowState(Qt::WindowNoState);
            winsize=false;
        }else{
            ui->btn_max->setStyleSheet("QPushButton#btn_max{border-image:url(:/nakiri/sou/复原.png);}");
            setWindowState(Qt::WindowMaximized);
            winsize=true;
        }
    });
    connect(ui->btn_min,&QPushButton::clicked,[=](){
        setWindowState(Qt::WindowMinimized);
    });

    //获取系统时间。
    QDateTime current_date_time =QDateTime::currentDateTime();
    current_date =current_date_time.toString("yyyy-MM-dd");

    //创建文件夹。
    QDir * edir = new QDir();
    QDir dirinfo("info");
    //如果文件夹不存在则创建。
    if(!dirinfo.exists()){
        edir->mkdir("info");
    }
    //关联edir与info文件夹。
    edir->setPath("./info");
    //获取文件个数。
    info_sum = edir->count();
    //不是空文件夹则执行。
    if(info_sum != 0){
        //获取所有的文件名。
        info_name = edir->entryList();

        for(const auto & k : info_name){
            if(k == "." || k == ".."){
                continue;
            }
            auto_file_name = k;
            //自动检测的判断打开。
            add_ok = true;
            emit on_btn_add_clicked();
        }
    }

    //创建记录壁纸的文件夹。
    QDir * wdir = new QDir;
    QDir walldata("wallpaper");
    //如果文件夹不存在则创建。
    if(!walldata.exists()){
        wdir->mkdir("wallpaper");
        QFile mkfile("./wallpaper/wallname.txt");
        mkfile.open(QIODevice::WriteOnly);
        mkfile.close();
    }else{
        //打开自动。
        wall_ok = true;
        QFile opfile("./wallpaper/wallname.txt");
        if(opfile.open(QIODevice::ReadWrite | QIODevice::Text)){
            QTextStream datain(&opfile);
            auto_wall_name = datain.readLine();
            emit on_btn_wallpaper_clicked();
        }
    }

    //数据库操作。
    QSqlDatabase database;

    if (QSqlDatabase::contains("Englist_sqlite"))
    {
        database.setUserName("qwertyuiop");
        database.setPassword("123456");
        database = QSqlDatabase::database("Englist_sqlite");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE","Englist_sqlite");
        // 设置数据库文件的名字
        database.setDatabaseName("Englist_sqlite.db");
        database.setUserName("qwertyuiop");
        database.setPassword("123456");
        datauser=database.userName();
        datapassword=database.password();
        database.open();
        // 用于执行sql语句的对象
        sqlQuery = new QSqlQuery("",database);
        //创建表格。
        sqlQuery->exec("create table Englishtable(id int primary key , daytext TEXT , sumall int ,rightsum int ,ratio REAL);");
        //创建完成后检测今天的数据是否生成。
        //需要将整个数据库跑一遍，顺便将自己的数据直接显示在tree控件上。
        sqlQuery->exec("SELECT * FROM Englishtable");
        while(sqlQuery->next()){
            max_i = sqlQuery->value(0).toInt();
            sqldata = sqlQuery->value(1).toString();
            qDebug() <<sqlQuery->value(0).toInt()<<sqlQuery->value(1).toString()<<sqlQuery->value(2).toInt()<<sqlQuery->value(3).toInt()<<sqlQuery->value(4).toDouble();
            data_all_sum = sqlQuery->value(2).toInt();
            data_right_sum = sqlQuery->value(3).toInt();
            data_right_ratio = sqlQuery->value(4).toDouble();

            QString rall ="总数:" + QString::number(data_all_sum) +"  正确数:" + QString::number(data_right_sum) +"  正确率:" + QString::number(data_right_ratio);
            QStringList testlist;
            testlist <<sqlQuery->value(1).toString()<<rall;
            QTreeWidgetItem * test = new QTreeWidgetItem(testlist);
            thisweek->addChild(test);

            total_day = max_i;
            total_sum += sqlQuery->value(2).toInt();
            total_right += sqlQuery->value(3).toInt();

        }

        total_ratio = double(total_right) / double(total_sum);
        QStringList totallist;
        QString rall = "总数:" + QString::number(total_sum)+"  正确数:" + QString::number(total_right) +"  正确率:" + QString::number(total_ratio);
        totallist << QString::number(total_day) <<rall;
        QTreeWidgetItem * test = new QTreeWidgetItem(totallist);
        lastweek->addChild(test);

        if(current_date == sqldata){
            //如果早就有了，则读入数据。
            qDebug() <<"already have";
            qDebug()<<data_all_sum<<data_right_sum<<data_right_ratio;
        }else{
            //没有今天的数据则要重写一个。
            qDebug() <<"don't have";
            max_i++;
            QString sqlexe = QString("INSERT INTO Englishtable VALUES(%1,'%2',0,0,0.0);").arg(max_i).arg(current_date);
            sqlQuery->exec(sqlexe);
            data_all_sum = 0;
            data_right_sum = 0;
            data_right_ratio = 0.0;
        }

        if(data_all_sum == 0){
            ui->label_today_sum->setText("还没有记单词。");
        }else{
            ui->label_today_sum->setText("单词数:" + QString::number(data_all_sum) + "  正确数:" + QString::number(data_right_sum) + "  正确率:" + QString::number(data_right_ratio));
        }
    }

    emit chart_update();

    x[0] = ui->label_4->x();
    y[0] = ui->label_4->y();
    x[1] = ui->label_5->x();
    y[1] = ui->label_5->y();
    x[2] = ui->label_6->x();
    y[2] = ui->label_6->y();
    x[3] = ui->label_7->x();
    y[3] = ui->label_7->y();

}

theWidget::~theWidget()
{
    delete ui;
}

//换壁纸的按键。
void theWidget::on_btn_wallpaper_clicked()
{
    if(wall_ok == false){
        QString wallx = QFileDialog::getOpenFileName(this,"选择文件",".","(*.jpg *.jpeg *.png .bmp)");
        QFileInfo wallpaperinfo(wallx);
        qDebug()<<wallpaperinfo.suffix();
        if(wallpaperinfo.suffix() != "\0"){
            wallpaper = wallx;
            //将文件复制粘贴到info文件夹。
            QFile copyfile(wallpaper);
            QFileInfo * wallinfo = new QFileInfo(copyfile);
            copyfile.copy("./wallpaper/" + wallinfo->fileName());
            //移除记录的文件。
            QFile::remove("./wallpaper/wallname.txt");
            //重新生成一个。
            QFile opwall("./wallpaper/wallname.txt");
            opwall.open(QIODevice::WriteOnly);
            opwall.close();
            if(opwall.open(QIODevice::ReadWrite | QIODevice::Text)){
                QTextStream datain(&opwall);
                datain <<"./wallpaper/" + wallinfo->fileName();
            }
        }
    }else{
        wallpaper = auto_wall_name;
        wall_ok = false;
    }

}

//画家类，主要用于绘制壁纸。
void theWidget::paintEvent(QPaintEvent *){

    QPainter painter(this);
    // 背景图片
    painter.drawPixmap(0,0,width(),height(),QPixmap(wallpaper));

}

//添加新的单词卡。
void theWidget::on_btn_add_clicked()
{

    if(add_ok == true){
        newcard[card_i] = "./info/" + auto_file_name;
    }else{
        newcard[card_i] = QFileDialog::getOpenFileName(this,"选择文件",".","(*.json)");
    }
    add_ok = false;
    //获取文件名。
    QFileInfo * fileinfo = new QFileInfo(newcard[card_i]);
    filebasename[card_i] = fileinfo->baseName();

    //判端文件地址是否有效。
    if(fileinfo->suffix()=="json"){
        //如果有效则执行下面的步骤。

        //将文件复制粘贴到info文件夹。
        QFile copyfile(newcard[card_i]);
        copyfile.copy("./info/" + fileinfo->fileName());

        if(card_i != 0){
            //先将单元格中本来就有的按钮移除并析构。
            for(int i = 0 ; i < sum_unit ; i++){
                btn_unit[i]->setParent(nullptr);
                unitlayout->removeWidget(btn_unit[i]);
                delete btn_unit[i];

            }
        }

        //动态生成单词卡的按钮。
        btn_card[card_i] = new QPushButton(filebasename[card_i],this);
        btn_card[card_i]->setFixedSize(230,150);
        btn_card[card_i]->setStyleSheet("QPushButton{background-color: rgb(100, 244, 175);border:2px groove gray;border-radius:20px;padding:2px 4px;border-style: outset;}QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");

        //设置下字体。
        QFont ft("Microsoft YaHei Light",12, 25);
        btn_card[card_i]->setFont(ft);

        cardlayout->addWidget(btn_card[card_i],card_i);
        ui->widget_card->setLayout(cardlayout);

        //然后动态创建单元的按钮。
        card_i_btn = card_i;
        emit create_unit();

        //连接单词卡按钮和章节按钮的生成。
        connect(btn_card[card_i],&QPushButton::clicked,this,&theWidget::sender_name);

        //将目前的card_i设置为选中的文件的。
        the_card_i = card_i;

        //添加新的单词卡的时候要额外使label_card_unit重置。
        ui->label_choice->setText(filebasename[card_i]+" Chapter 0");

        //最后在++，使下一个按钮加一位。
        card_i++;

    }else{
        //QMessageBox::critical(this,"错误","文件打开失败，文件格式不正确！","确定");
    }

}

//解析json文件并动态创建单元按钮。
void theWidget::create_unit(){

    QFile jsonfile(newcard[card_i_btn]);//json文件的读写。
    jsonfile.open(QIODevice::ReadOnly);//只读。
    QByteArray jsondata = jsonfile.readAll();//将读取的文件转化为二进制。
    jsonfile.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsondata,&parseError);//转化为json文档。
    if(!doc.isNull()&&(parseError.error == QJsonParseError::NoError)){
        //解析没错。

        if (doc.isArray()) { // JSON文档为数组。
            QJsonArray array = doc.array();

            nSize = array.size();  // 获取数组大小

            //判读数组大小应该分割为多少个单元，20为一个单位。
            more_unit_num = nSize % 20;
            sum_unit = (nSize - more_unit_num) / 20;
            if(more_unit_num!=0){
                sum_unit++;
            }

            for (int i = 0; i < nSize ; i++) {  // 遍历数组
                QJsonValue value = array.at(i);
                QJsonObject subObj=value.toObject();

                QJsonValue wordnameTemp = subObj.value("name");//将name中的值传给这个变量。
                unitword[i] = wordnameTemp.toString();//将这个变量转化为QString。

                QJsonValue usphoneTemp = subObj.value("usphone");
                usphone[i] = usphoneTemp.toString();

                QJsonValue ukphoneTemp = subObj.value("ukphone");
                ukphone[i] = ukphoneTemp.toString();

                if (subObj.contains("trans")) {
                    QJsonValue value = subObj.value("trans");
                    if (value.isArray()) {
                        QJsonArray transarray = value.toArray();
                        int Size = transarray.size();
                        //先把上一次的归零。
                        for(int j = 0 ; j < 3 ; j++){
                            unittrans[i][j] = "\0";
                        }
                        for (int j = 0; j < Size; j++) {
                            QJsonValue value = transarray.at(j);
                            unittrans[i][j] = value.toString();
                        }
                    }
                }
            }
            for(int i = nSize ; i <= 4000; i++){
                if(unitword[i]=="\0"){
                    break;
                }else{
                    unitword[i] = "\0";
                    usphone[i] = "\0";
                    ukphone[i] = "\0";
                }
            }
        }
    }else{
        QMessageBox::critical(this,"错误","文件打开失败，文件格式不正确！","确定");
    }

    //使用栅格布局管理器。
    int x = 0 , y = 0;
    for(int i = 0 ; i < sum_unit ; i++){
        QString unitnum = QString::number(i);
        QString unittext = "Chapter "+ unitnum;
        btn_unit[i] = new QPushButton(unittext , this);

        QFont ft("Microsoft YaHei Light",12, 25);
        btn_unit[i]->setFont(ft);

        btn_unit[i]->setFixedSize(200,200);
        unitlayout->addWidget(btn_unit[i],y,x);
        x++;
        if(x == 4){
            x = 0;
            y++;
        }

        btn_unit[i]->setStyleSheet("QPushButton{background-color: rgb(100, 244, 175);border:2px groove gray;border-radius:20px;padding:2px 4px;border-style: outset;}QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");

        //连接单元的按钮与练习的内容。
        connect(btn_unit[i],&QPushButton::clicked,this,&theWidget::sender_name_unit);
    }
    ui->widget_unit->setLayout(unitlayout);

}

void theWidget::sender_name(){

    //当点击单词卡按钮的时候先断开之前的连接。
    disconnect(ui->btn_enter,&QPushButton::clicked,this,&theWidget::enterword);

    //先用sender来找到点击的按钮的名字。
    QPushButton *pBtn = (QPushButton*)sender();

    //通过判断文件名判断哪一个按钮被点击。
    for(int i = 0 ; i < card_i ; i++){
        if(pBtn->text()==filebasename[i]){
            btn_card[i]->setStyleSheet("QPushButton{background-color: rgb(204, 228, 247);border:2px groove gray;border-radius:20px;padding:2px 4px;border-style: outset;}QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
            card_i_btn = i;
        }else{
            btn_card[i]->setStyleSheet("QPushButton{background-color: rgb(100, 244, 175);border:2px groove gray;border-radius:20px;padding:2px 4px;border-style: outset;}QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
        }
    }

    //先将单元格中本来就有的按钮移除并析构,注意此sum_unit还保留着上一个card的个数。
    for(int i = 0 ; i < sum_unit ; i++){

        btn_unit[i]->setParent(nullptr);
        unitlayout->removeWidget(btn_unit[i]);
        delete btn_unit[i];

    }

    //然后再次动态布局生成按键。
    emit create_unit();

    //选择新的单词卡的时候要额外使label_card_unit重置。
    ui->label_choice->setText(pBtn->text()+" Chapter 0");
}

//两个换页的按钮。
void theWidget::on_btn_page_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    mainwin=false;
}
void theWidget::on_btn_page2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    mainwin=true;
}

//单元按钮的槽函数，用于存放单元格中的单词数据。
void theWidget::sender_name_unit(){

    //当点击单元按钮的时候先断开之前的连接,使单词页面不能enter。
    disconnect(ui->btn_enter,&QPushButton::clicked,this,&theWidget::enterword);
    //然后将label的内容清空。
    ui->label_trans->setText("");
    ui->label_phone->setText("");
    ui->label_rw->setText("");

    //先用sender来找到点击的按钮的名字。
    QPushButton *pBtn = (QPushButton*)sender();

    //通过判断文件名判断哪一个按钮被点击。
    for(int i = 0 ; i < sum_unit ; i++){
        QString boolname = "Chapter "+ QString::number(i);
        if(pBtn->text()==boolname){
            //按钮的编号记录在unit_i中。
            unit_i = i;
            btn_unit[i]->setStyleSheet("QPushButton{background-color: rgb(204, 228, 247);border:2px groove gray;border-radius:20px;padding:2px 4px;border-style: outset;}QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
        }else{
            btn_unit[i]->setStyleSheet("QPushButton{background-color: rgb(100, 244, 175);border:2px groove gray;border-radius:20px;padding:2px 4px;border-style: outset;}QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
        }
    }

    ui->label_choice->setText(filebasename[card_i_btn] + " Chapter " + QString::number(unit_i));
}

//开始的按钮。
void theWidget::on_btn_start_clicked()
{
    //开始按钮已按下。
    if(start_ok == false){
        start_ok = true;
    }

    ui->label_rw->setText(" ");
    disconnect(ui->btn_enter,&QPushButton::clicked,this,&theWidget::enterword);
    ui->label_right_sum->setText("正确数:0");
    ui->label_right_ratio->setText("正确率:0");
    ui->label_time->setText("时间:00:00");
    //计时器开始。
    s = 0;
    m = 0;
    tm->start(1000);

    //正确数与正确率总数归零。
    right_sum = 0;
    right_ratio = 0.0;

    //通过判断card_i来判断是否已经有文件。
    if(card_i != 0){
        word_i = unit_i * 20;
        next_word_i = word_i;

        //如果开启英语展示被打开。
        if(en_show == true){
            ui->label_rw->setText(unitword[word_i]);
        }

        //将翻译分段显示。
        QString trans_str;
        int j = 0;
        while(unittrans[next_word_i][j]!="\0"){
            trans_str += unittrans[next_word_i][j];
            trans_str += "\n";
            j++;
        }
        ui->label->setWordWrap(true);
        ui->label_trans->setText(trans_str);

        //判断音标是否为空，没有音标就不显示。
        if(usphone[next_word_i]!="\0" && phone_switch == true){
            QString phone_str = "us:"+usphone[next_word_i]+" uk:"+ukphone[next_word_i];
            ui->label_phone->setText(phone_str);
        }

        //连接确认的按钮。
        connect(ui->btn_enter,&QPushButton::clicked,this,&theWidget::enterword);

    }else{
        QMessageBox::critical(this,"错误","未选中文件！","确定");
    }
}

void theWidget::enterword(){
    if(en_show == false){

        //判断输入是否正确。
        if(ui->lineEdit->text()==unitword[next_word_i]){
            right_sum++;
            ui->label_rw->setText("正确");
        }else{
            ui->label_rw->setText(ui->lineEdit->text()+"错误，正确拼写为 "+unitword[next_word_i]);
        }

        //设置为正确个数的显示。
        ui->label_right_sum->setText("正确数:" + QString::number(right_sum));

        next_word_i++;

        //计算正确率。
        right_ratio = double(right_sum) / double(next_word_i - word_i);
        if(right_ratio < 0){
            right_ratio = 0;
        }
        ui->label_right_ratio->setText("正确率:" + QString::number(right_ratio));

        //如果已经是最后一个，则断开连接。
        if(next_word_i - word_i == 20 || unitword[next_word_i] == "\0"){
            disconnect(ui->btn_enter,&QPushButton::clicked,this,&theWidget::enterword);
            //开始按钮重置。
            start_ok = false;
            //关闭计时器。
            tm->stop();

            //使用数据库进行处理。
            data_all_sum  += next_word_i - word_i;
            data_right_sum += right_sum;
            data_right_ratio = data_right_sum / double(data_all_sum);
            QString sqlexe = QString("UPDATE Englishtable SET sumall=%1,rightsum=%2,ratio=%3 WHERE id=%4;").arg(data_all_sum).arg(data_right_sum).arg(data_right_ratio).arg(max_i);
            sqlQuery->exec(sqlexe);

            ui->label_today_sum->setText("单词数:" + QString::number(data_all_sum) + "  正确数:" + QString::number(data_right_sum) + "  正确率:" + QString::number(data_right_ratio));
        }else{
            QString trans_str;
            int j = 0;
            while(unittrans[next_word_i][j]!="\0"){
                trans_str += unittrans[next_word_i][j];
                trans_str += "\n";
                j++;
            }

            //判断音标是否为空，没有音标就不显示。
            if(usphone[next_word_i]!="\0" && phone_switch == true){
                QString phone_str = "us:"+usphone[next_word_i]+"  uk:"+ukphone[next_word_i];
                ui->label_phone->setText(phone_str);
            }

            ui->label_trans->setText(trans_str);
        }

        //清空lineEdit的内容。
        ui->lineEdit->clear();
    }else{

        next_word_i++;
        //如果已经是最后一个，则断开连接。
        if(next_word_i - word_i == 20 || unitword[next_word_i] == "\0"){
            disconnect(ui->btn_enter,&QPushButton::clicked,this,&theWidget::enterword);
            //开始按钮重置。
            start_ok = false;
            //停止计时器。
            tm->stop();
        }else{
            ui->label_rw->setText(unitword[next_word_i]);
            QString trans_str;
            int j = 0;
            while(unittrans[next_word_i][j]!="\0"){
                trans_str += unittrans[next_word_i][j];
                trans_str += "\n";
                j++;
            }

            //判断音标是否为空，没有音标就不显示。
            if(usphone[next_word_i]!="\0" && phone_switch == true){
                QString phone_str = "us:"+usphone[next_word_i]+"  uk:"+ukphone[next_word_i];
                ui->label_phone->setText(phone_str);
            }

            ui->label_trans->setText(trans_str);
        }
    }

}

void theWidget::on_btn_phone_clicked()
{
    if(phone_switch == false){
        ui->btn_phone->setText("关闭音标显示");
        if(ui->label_trans->text() != "\0"){
            if(usphone[next_word_i]!="\0"){
                QString phone_str = "us:"+usphone[next_word_i]+"  uk:"+ukphone[next_word_i];
                ui->label_phone->setText(phone_str);
            }
        }
        phone_switch = true;
    }else{
        ui->btn_phone->setText("开启音标显示");
        QString phone_str = "\0";
        ui->label_phone->setText(phone_str);
        phone_switch = false;
    }
}

void theWidget::on_btn_voice_clicked()
{
    if(unitword[next_word_i] != "\0"){
        playlist->clear();
        QString word_url = "https://dict.youdao.com/dictvoice?audio=" + unitword[next_word_i];
        playlist->addMedia(QUrl(word_url));
        player->play();
        ui->btn_voice->setStyleSheet("QPushButton#btn_voice{border-image:url(:/nakiri/sou/声音.png);}");
        tm2->start(100);
    }else{
        QMessageBox::critical(this,"错误","没有已显示的单词！","确定");
    }
}

void theWidget::on_btn_page3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void theWidget::on_btn_pageback_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void theWidget::on_btn_en_show_clicked()
{

    if(en_show == true){
        ui->btn_en_show->setText("开启英语显示");
        ui->label_rw->setText("\0");
        en_show = false;
    }else{
        ui->btn_en_show->setText("关闭英语显示");
        if(ui->label_trans->text() != "\0"){
            ui->label_rw->setText(unitword[next_word_i]);
        }
        en_show = true;
    }
}

void theWidget::on_btn_test_clicked()
{
    ui->label_4->setGeometry(x[0],y[0],ui->label_4->width(),ui->label_4->height());
    ui->label_5->setGeometry(x[1],y[1],ui->label_5->width(),ui->label_5->height());
    ui->label_6->setGeometry(x[2],y[2],ui->label_6->width(),ui->label_6->height());
    ui->label_7->setGeometry(x[3],y[3],ui->label_7->width(),ui->label_7->height());

    //通过跑一遍数据库来确认实时数据。
    sqlQuery->exec("SELECT * FROM Englishtable");
    mouth_day=0;
    mouth_all_sum =0;
    while(sqlQuery->next()){
           QString str1 = sqlQuery->value(1).toString();
           char * str2;
           QByteArray bb = str1.toLatin1();
           str2=bb.data();
           QDateTime current_date_time =QDateTime::currentDateTime();
           QString str3 = current_date_time.toString("yyyy-MM");
           char * str4;
           QByteArray ba = str3.toLatin1();
           str4=ba.data();
           for(int i = 0;i <= 6 ;i++){
               if(str2[i] != str4[i]){
                   break;
               }
               if(i==6){
                   mouth_day++;
                   mouth_all_sum += sqlQuery->value(2).toInt();
               }
           }
    }

    ui->label_4->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->label_4->setText(QString("今天，你记了 %1 个单词。  ").arg(data_all_sum));
    ui->label_5->setText(QString("   其中正确的个数为 %1。").arg(data_right_sum));
    ui->label_6->setText(QString("你在本月内学习了 %1 天。  ").arg(mouth_day));
    ui->label_7->setText(QString("   一共记了 %1 个单词").arg(mouth_all_sum));
    //qDebug() <<ani_i;
    ui->stackedWidget->setCurrentIndex(4);
    QPropertyAnimation * ani = new QPropertyAnimation(ui->label_4,"geometry",this);
    ani->setStartValue(ui->label_4->geometry());
    ani->setEndValue(QRect(ui->label_4->x()+650,ui->label_4->y(),ui->label_4->width(),ui->label_4->height()));
    ani->setDuration(2000);
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start(QAbstractAnimation::DeleteWhenStopped);
    QPropertyAnimation * ani2 = new QPropertyAnimation(ui->label_5,"geometry",this);
    ani2->setStartValue(ui->label_5->geometry());
    ani2->setEndValue(QRect(ui->label_5->x()-650,ui->label_5->y(),ui->label_5->width(),ui->label_5->height()));
    ani2->setDuration(2000);
    ani2->setEasingCurve(QEasingCurve::OutBounce);
    ani2->start(QAbstractAnimation::DeleteWhenStopped);
    QPropertyAnimation * ani3 = new QPropertyAnimation(ui->label_6,"geometry",this);
    ani3->setStartValue(ui->label_6->geometry());
    ani3->setEndValue(QRect(ui->label_6->x()+650,ui->label_6->y(),ui->label_6->width(),ui->label_6->height()));
    ani3->setDuration(2000);
    ani3->setEasingCurve(QEasingCurve::OutBounce);
    ani3->start(QAbstractAnimation::DeleteWhenStopped);
    QPropertyAnimation * ani4 = new QPropertyAnimation(ui->label_7,"geometry",this);
    ani4->setStartValue(ui->label_7->geometry());
    ani4->setEndValue(QRect(ui->label_7->x()-650,ui->label_7->y(),ui->label_7->width(),ui->label_7->height()));
    ani4->setDuration(2000);
    ani4->setEasingCurve(QEasingCurve::OutBounce);
    ani4->start(QAbstractAnimation::DeleteWhenStopped);

}

void theWidget::on_btn_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void theWidget::mouseMoveEvent(QMouseEvent *event){

    int dx = event->globalX() - mousePoint.x();
    int dy = event->globalY() - mousePoint.y();
    mousePoint = event->globalPos();
    move(this->pos().x()+dx,this->pos().y()+dy);
}

void theWidget::mousePressEvent(QMouseEvent *event){
    mousePoint=event->globalPos();
}

void theWidget::mouseReleaseEvent(QMouseEvent *event){
    int dx = event->globalX() - mousePoint.x();
    int dy = event->globalY() - mousePoint.y();
    move(this->pos().x()+dx,this->pos().y()+dy);
}

//更新折线图的数据。
void theWidget::chart_update(){

    chart_i = 10;
    //设置折线图的数据。
    series = new QLineSeries();
    //设置折线图表。
    chart = new QChart();
    //跑一遍数据库，添加测试数据。
    sqlQuery->exec("SELECT * FROM Englishtable");

    //X坐标。
    axisX = new QCategoryAxis;
    axisX->setMin(0);
    axisX->setMax(10);
    axisX->setStartValue(0);

    //判断数据。
    while(sqlQuery->next()){

        //开启判断数据。
        if(sqlQuery->value(0).toInt() == max_i - chart_i){

            QString str1 = sqlQuery->value(1).toString().mid(5);
            qDebug()<<str1;

            //append要按照大小顺序依次添加
            axisX->append(sqlQuery->value(1).toString(),10-chart_i);
            //下边这一句代码的作用是让刻度线和刻度的label对齐
            axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
            //设置内容。
            axisX->append(str1,sqlQuery->value(0).toInt()-1);
            series->append(max_i - chart_i,sqlQuery->value(2).toInt());
            chart_i--;
        }else if(max_i - chart_i < 0){

            //变成char*
            QString str1 = sqlQuery->value(1).toString().mid(5);

            qDebug()<<str1;

            axisX->append(str1,sqlQuery->value(0).toInt()-1);
            axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
            series->append(sqlQuery->value(0).toInt()-1,sqlQuery->value(2).toInt());
        }
    }

    QFont ftc("Microsoft YaHei Light",9, 25);
    QFont ftt("Microsoft YaHei Light",15, 25);
    axisX->setLabelsFont(ftc);
    chart->setTitleFont(ftt);

    // 将图例隐藏
    chart->legend()->hide();
    // 关联series，这一步很重要，必须要将series关联到QChart才能将数据渲染出来。
    chart->addSeries(series);
    // 开启OpenGL，QLineSeries支持GPU绘制，Qt其他有的图表类型是不支持的。
    series->setUseOpenGL(true);
    // 创建默认的坐标系（笛卡尔坐标）
    chart->createDefaultAxes();
    // 设置图表标题
    chart->setTitle(QStringLiteral("最近的数据"));
    //设置横坐标。
    chart->setAxisX(axisX,series);

    QChartView *view = new QChartView(chart);
    // 开启抗锯齿，让显示效果更好
    view->setRenderHint(QPainter::Antialiasing);
    view->resize(800,450);
    // 显示图表
    view->setParent(ui->widget_charts);
}

//到制作页面。
void theWidget::on_btn_make_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

//从新建返回向主页面。
void theWidget::on_btn_return_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void theWidget::on_btn_nextword_clicked()
{
    if(ui->lineEdit_word->text() == "\0" || ui->lineEdit_trans->text() == "\0"){
        QMessageBox::critical(this,"错误","没有输入单词或翻译！","确定");
    }else{
        //获取现在输入的信息。
        new_word[new_word_card_i] = ui->lineEdit_word->text();
        new_trans[new_word_card_i] = ui->lineEdit_trans->text();
        new_usphone[new_word_card_i] = ui->lineEdit_usphone->text();
        new_ukphone[new_word_card_i] = ui->lineEdit_ukphone->text();
        //新单词的计数器自加一个。
        new_word_card_i++;
        //然后设置成下一个。
        ui->lineEdit_word->setText(new_word[new_word_card_i]);
        ui->lineEdit_trans->setText(new_trans[new_word_card_i]);
        ui->lineEdit_usphone->setText(new_usphone[new_word_card_i]);
        ui->lineEdit_ukphone->setText(new_ukphone[new_word_card_i]);
    }
}

void theWidget::on_btn_save_clicked()
{
    //先将已经写了的录入数组中。
    new_word[new_word_card_i] = ui->lineEdit_word->text();
    new_trans[new_word_card_i] = ui->lineEdit_trans->text();
    new_usphone[new_word_card_i] = ui->lineEdit_usphone->text();
    new_ukphone[new_word_card_i] = ui->lineEdit_ukphone->text();
    //保存的时候，先生成文件。
    new_filename_str = ui->lineEdit_file->text();
    //然后把所有的重置。
    ui->lineEdit_word->setText("\0");
    ui->lineEdit_trans->setText("\0");
    ui->lineEdit_usphone->setText("\0");
    ui->lineEdit_ukphone->setText("\0");
    ui->lineEdit_file->setText("\0");

    if(new_filename_str =="\0"){
        QMessageBox::critical(this,"错误","没有输入文件名！","确定");
    }else{
        QMessageBox::information(this,"单词本",QString("已保存文件%1.json").arg(new_filename_str),"确定");
        //创建新的json文件。
        QFile newfile("./info/"+new_filename_str+".json");
        newfile.open(QIODevice::WriteOnly);
        newfile.close();

        // 构建 Json 数组。
        QJsonArray obArray;//主数组。
        QJsonArray transarray;//trans的数组。
        QJsonObject pageObject;//主数组中的object.

        //循环取值并插入。
        for(int i = 0 ; i < 1000; i++){

            if(new_word[i] == "\0"){
                break;
            }

            transarray.removeFirst();
            //获取四个键值对。
            transarray.append(new_trans[i]);
            pageObject.insert("name",new_word[i]);
            pageObject.insert("trans",QJsonValue(transarray));
            pageObject.insert("usphone",new_usphone[i]);
            pageObject.insert("ukphone",new_ukphone[i]);

            //输入到主数组中。
            obArray.append(pageObject);

        }

        // 构建 Json 文档
        QJsonDocument document;
        document.setArray(obArray);
        QByteArray byteArray = document.toJson(QJsonDocument::Compact);
        QString strJson(byteArray);

        if (!newfile.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug() << "file error!";
        }
        QTextStream in(&newfile);
        in.setCodec("UTF-8");
        in << strJson;

        newfile.close();
        //将新单词卡的个数设置为0。
        new_word_card_i = 0;
    }
}

void theWidget::on_btn_lastword_clicked()
{
    if(new_word_card_i - 1 < 0){
        QMessageBox::critical(this,"错误","已经是第一个了！","确定");
    }else{
        //如果有输入的话。
        if(ui->lineEdit_word->text()!="\0"){
            //先将已经写了的录入数组中。
            new_word[new_word_card_i] = ui->lineEdit_word->text();
            new_trans[new_word_card_i] = ui->lineEdit_trans->text();
            new_usphone[new_word_card_i] = ui->lineEdit_usphone->text();
            new_ukphone[new_word_card_i] = ui->lineEdit_ukphone->text();
        }
        //然后返回上一个。
        new_word_card_i--;
        ui->lineEdit_word->setText(new_word[new_word_card_i]);
        ui->lineEdit_trans->setText(new_trans[new_word_card_i]);
        ui->lineEdit_usphone->setText(new_usphone[new_word_card_i]);
        ui->lineEdit_ukphone->setText(new_ukphone[new_word_card_i]);
    }
}

void theWidget::on_btn_in_clicked()
{
    QString import_file_name = QFileDialog::getOpenFileName(this,"选择文件",".","(*.json)");
    QFile jsonfile(import_file_name);//json文件的读写。
    jsonfile.open(QIODevice::ReadOnly);//只读。
    QByteArray jsondata = jsonfile.readAll();//将读取的文件转化为二进制。
    jsonfile.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsondata,&parseError);//转化为json文档。
    if(!doc.isNull()&&(parseError.error == QJsonParseError::NoError)){
        //解析没错。

        if (doc.isArray()) { // JSON文档为数组。
            QJsonArray array = doc.array();

            nSize = array.size();  // 获取数组大小

            for (int i = 0; i < nSize ; i++) {  // 遍历数组
                QJsonValue value = array.at(i);
                QJsonObject subObj=value.toObject();

                QJsonValue wordnameTemp = subObj.value("name");//将name中的值传给这个变量。
                new_word[i] = wordnameTemp.toString();//将这个变量转化为QString。

                QJsonValue usphoneTemp = subObj.value("usphone");
                new_usphone[i] = usphoneTemp.toString();

                QJsonValue ukphoneTemp = subObj.value("ukphone");
                new_ukphone[i] = ukphoneTemp.toString();

                if (subObj.contains("trans")) {
                    QJsonValue value = subObj.value("trans");
                    if (value.isArray()) {
                        QJsonArray transarray = value.toArray();
                        int Size = transarray.size();
                        for (int j = 0; j < Size; j++) {
                            QJsonValue value = transarray.at(j);
                            new_trans[i] = value.toString();
                        }
                    }
                }
            }
        }
        //读写完成后先归零，然后再显示。
        new_word_card_i =0;
        QFileInfo * import_file_info = new QFileInfo(import_file_name);
        ui->lineEdit_file->setText(import_file_info->baseName());
        ui->lineEdit_word->setText(new_word[new_word_card_i]);
        ui->lineEdit_trans->setText(new_trans[new_word_card_i]);
        ui->lineEdit_usphone->setText(new_usphone[new_word_card_i]);
        ui->lineEdit_ukphone->setText(new_ukphone[new_word_card_i]);
    }else{
        //QMessageBox::critical(this,"错误","文件打开失败，文件格式不正确！","确定");
    }
}


void theWidget::on_btn_login_clicked()
{
    if(ui->lineEdit_user->text() != datauser){
        ui->lineEdit_user->setText("\0");
        ui->lineEdit_user->setPlaceholderText("用户名错误");
        ui->lineEdit_pwd->setText("\0");
        ui->lineEdit_pwd->setPlaceholderText("input your password");
    }else if(ui->lineEdit_pwd->text() != datapassword){
        ui->lineEdit_pwd->setText("\0");
        ui->lineEdit_pwd->setPlaceholderText("密码错误");
    }else{
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void theWidget::keyPressEvent(QKeyEvent * event){
    switch (event->key())
    {
        //回车键。
        case Qt::Key_Return:
            //当界面是4的时候，登录界面。
            if(ui->stackedWidget->currentIndex() == 5){
                emit on_btn_login_clicked();
            }else if(ui->stackedWidget->currentIndex() == 0){
                emit on_btn_page_clicked();
            }else if(ui->stackedWidget->currentIndex() == 1){
                emit ui->btn_enter->clicked();
            }else if(ui->stackedWidget->currentIndex() == 3){
                emit on_btn_nextword_clicked();
            }
            break;
        case Qt::Key_Escape:
            if(ui->stackedWidget->currentIndex() == 3){
                emit on_btn_lastword_clicked();
            }
            break;
    }
}
