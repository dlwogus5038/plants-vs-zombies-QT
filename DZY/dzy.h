#ifndef DZY_H
#define DZY_H

#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QtGui>
#include <QtMultimedia/QMediaPlayer>
#include <QFile>
#include <QtMultimedia/QSound>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPoint>

namespace Ui {
class dzy;
}

class MyGame;
class TOOTBtn;
class FlowerSun;
class SunFlower;
class ClassicZombie;
class BucketZombie;
class PoleZombie;
class WallNut;
class Peashooter;

class dzy : public QMainWindow
{
    Q_OBJECT

public:
    explicit dzy(QWidget *parent = 0);
    ~dzy();

private:
    Ui::dzy *ui;
};


class DragItem1 : public QLabel
{
    Q_OBJECT

public:
    DragItem1(QWidget *parent=0);
};

class DragItem2 : public QLabel
{
    Q_OBJECT

public:
    DragItem2(QWidget *parent=0);
};

class DragItem3 : public QLabel
{
    Q_OBJECT

public:
    DragItem3(QWidget *parent=0);
};

class DragItem4 : public QLabel
{
    Q_OBJECT

public:
    DragItem4(QWidget *parent=0);
};

class MyGame : public QWidget
{
    Q_OBJECT
public:
    MyGame(){}
    void MyGameStart();
    void MyBackground();
    void MyStartMusic();
    void ZombieHandMusic();
    void MoveCard();
    void SetSunValue();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void CDeleteP(int i,int k);
    void BDeleteP(int i,int k);
    void PDeleteP(int i,int k);
    void CheckAllDie(int j);
    void CheckFail(int j);

    int SetSunNum = 0;
    int SunValueNum = 200;
signals:
    void NewGameSt();
    void GSsignal();
public slots:
    void OnPressBtn();
    void OnReleaseBtn();
    void ZombieHand();
    void TwinkleBtn();
    void ZH();
    void TB1();
    void TB2();
    void CountTime();
    void HideThisW();
    void NewGameBackG();
    void GameBGM();
    void ZombieHandMusic2();
    void AnimStart();
    void GameStart();
    void QPAStart1();
    void QPAStart2();
    void SetCard();
    void SetMyBox();
    void CoolDown1();
    void CoolDown2();
    void CoolDown3();
    void SetSun();
    void GetSun();
    void SSVS();
    void CCheckP();
    void BCheckP();
    void PCheckP();
    void CreateCZ();
    void CreateBZ();
    void CreatePZ();
    void CheckPZ();
    void Victory();
    void FailSlot();

private:
    QPushButton * QPB;
    QPushButton * PlantCard1;
    QPushButton * PlantCard2;
    QPushButton * PlantCard3;
    QPushButton * SunBtn;

    QTimer * CT;
    QTimer * ZHtimer;
    QTimer * TB1timer;
    QTimer * TB2timer;
    QTimer * BGMtimer;
    QTimer * CDTimer1;
    QTimer * CDTimer2;
    QTimer * CDTimer3;
    QTimer * SSTimer;
    QTimer * CCZTimer;
    QTimer * CBZTimer;
    QTimer * CPZTimer;
    QTimer * QPAT;
    QTimer * QPAT1;
    QTimer * QPAT2;
    QTimer * CEatP;
    QTimer * BEatP;
    QTimer * PEatP;
    QTimer * CheckPeaZombie;

    QLabel * label;
    QLabel * BGlabel;
    QLabel * SunLabel;
    QLabel * SunValueLabel;
    QLabel * PCard1;
    QLabel * PCard2;
    QLabel * PCard3;
    QLabel *** MyBox;
    QLabel * PeaPrice;
    QLabel * SunPrice;
    QLabel * WallPrice;
    QLabel * Shovel;
    QLabel * ShovelBack;

    QMediaPlayer * player;
    QMediaPlayer * player2;
    QMediaPlayer * DirtR;
    QMediaPlayer * GameBGM1;
    QMediaPlayer * CEP[5];
    QMediaPlayer * BEP[5];
    QMediaPlayer * PEP[5];
    QMediaPlayer * PeaShoot;
    QMediaPlayer * WinMusic;

    QMediaPlaylist * DirtRList;
    QMediaPlaylist * mediaList;
    QMediaPlaylist * mediaList2;
    QMediaPlaylist * BGMList1;
    QMediaPlaylist * CEPList[5];
    QMediaPlaylist * BEPList[5];
    QMediaPlaylist * PEPList[5];
    QMediaPlaylist * PeaShootList;
    QMediaPlaylist * WinMusiclist;

    QPropertyAnimation * QPA1;
    QPropertyAnimation * QPA2;

    QPropertyAnimation * MoveS1;
    QPropertyAnimation * MoveC1;
    QPropertyAnimation * MoveC2;
    QPropertyAnimation * MoveC3;
    QPropertyAnimation * MoveSH;
    QPropertyAnimation * MoveSHB;

    DragItem1 * DIT1;
    DragItem2 * DIT2;
    DragItem3 * DIT3;
    DragItem4 * DIT4;

    QString SunString;

    TOOTBtn * btn1;

    ClassicZombie * CZombie[5];
    PoleZombie * PZombie[5];
    BucketZombie * BZombie[5];

    SunFlower * SF[9][5];
    WallNut * WN[9][5];
    Peashooter * PS[9][5];


    int CEating = 0;
    int BEating = 0;
    int PEating = 0;


    int CZNum = 0;
    int BZNum = 0;
    int PZNum = 0;

    int TTNum = 0;
    int HandNum = 0;
    int ZHNum = 0;
    int CountN = 0;
    int TBNum = 0;

    int m_dragging = -1;

    int image1_x = 0;

    int m_PCBtn1 = -1;
    int m_PCBtn2 = -1;
    int m_PCBtn3 = -1;

    int i=0;


    int DITNum1=0;
    int DITNum2=0;
    int DITNum3=0;
    int DITNum4=0;

    int MyBoxState[9][5];

    int PeaPriceNum = 100;
    int SunPriceNum = 50;
    int WallPriceNum = 50;

    int PeaCDvalue = 0;
    int SunCDvalue = 0;
    int WallCDvalue = 0;

    int Px=0;
    int Py=0;

    int * PSun;

    int CZombieEat[5];
    int BZombieEat[5];
    int PZombieEat[5];

    int ZombieNumber = 11;
    int DieNumber = 0;

    bool CanCS=FALSE;

    bool Fail = FALSE;
    bool Sun1D = TRUE;
    bool Sun2D = TRUE;
    bool Sun3D = TRUE;

};

class TOOTBtn : public QPushButton
{
    Q_OBJECT
public:
    TOOTBtn(const QString &imgPath, QWidget *parent = 0 ,int SetSunNum = 0)
        : QPushButton(parent)
    {
        if(!imgPath.isEmpty()){
        _movie = new QMovie(imgPath, QByteArray(), this);
        connect(_movie, SIGNAL(frameChanged(int)), this, SLOT(iconChged(int)));
        connect(this,SIGNAL(clicked()),this,SLOT(MyClicked()));
        _movie->start();
       }

        this->setStyleSheet("QPushButton{border: none;}"
                               "QPushButton:hover { color: argb (0, 0, 0, 0%); }"
                               "QPushButton:pressed{border: none;}");
        this->move(100,-75);
        this->show();

        MS = new QPropertyAnimation(this,"geometry");
        MS->setDuration(6000);
        MS->setStartValue(QRect(100 + SetSunNum*20 , -75 , 76 , 75));
        MS->setEndValue(QRect(100 + SetSunNum*20 ,500,76,75));
        MS->start();

        SunD = FALSE;

        TimeOverSun = new QTimer;

        TimeOverSun->start(12000);

        connect(TimeOverSun,SIGNAL(timeout()),this,SLOT(TimeOverDelete()));

    }
    QPropertyAnimation * MS;

private slots:
    void iconChged(int){

        QTextDocument Text;

        QPixmap currFrame = _movie->currentPixmap();
        QPixmap pixmap(currFrame.width(), currFrame.height());
        pixmap.fill( Qt::transparent );
        QPainter painter( &pixmap );
        painter.drawPixmap(( pixmap.width()-currFrame.width()) / 2  ,
                           ( pixmap.height()-currFrame.height()) / 2, currFrame );
        Text.drawContents(&painter, pixmap.rect());

        setIcon(QIcon( pixmap));
        setIconSize(pixmap.rect().size());
    }

public slots:
    void MyClicked()
    {
        MSTimer = new QTimer;
        MS->stop();
        MS->setDuration(500);
        MSTimer->start(500);
        MS->setStartValue(QRect(this->pos().x() , this->pos().y() , 76 , 75));
        MS->setEndValue(QRect(0,0,76,75));
        MS->setEasingCurve(QEasingCurve::InOutCubic);
        MS->start();

        QMediaPlayer * points = new QMediaPlayer;
        points->setMedia(QUrl("points.mp3"));
        points->play();

        connect(MSTimer,SIGNAL(timeout()),this,SLOT(DeleteSun()));
    }

    void DeleteSun()
    {
        delete MSTimer;
        SunD = TRUE;
        delete this;
    }

    void TimeOverDelete()
    {
        delete TimeOverSun;
        if(SunD == FALSE)
        {
            delete this;
        }
    }

private:
    QMovie *_movie;
    QTimer * MSTimer;
    int i = 0;
    QTimer * TimeOverSun;
    bool SunD = TRUE;


};

class FlowerSun : public QPushButton
{
    Q_OBJECT
public:
    FlowerSun(const QString &imgPath, QWidget *parent = 0 ,int Px=0 ,int Py=0)
        : QPushButton(parent)
    {
        if(!imgPath.isEmpty()){
        _movie = new QMovie(imgPath, QByteArray(), this);
        connect(_movie, SIGNAL(frameChanged(int)), this, SLOT(iconChged(int)));
        connect(this,SIGNAL(clicked()),this,SLOT(MyClicked()));
        _movie->start();
       }

        this->setStyleSheet("QPushButton{border: none;}"
                               "QPushButton:hover { color: argb (0, 0, 0, 0%); }"
                               "QPushButton:pressed{border: none;}");
        this->move(Px,Py);
        this->show();

        MS = new QPropertyAnimation(this,"geometry");
        MS->setDuration(500);
        MS->setStartValue(QRect(this->pos().x() , this->pos().y() , 76 , 75));
        MS->setEndValue(QRect(this->pos().x() , this->pos().y() + 30 ,76,75));
        MS->start();

        SunD = FALSE;

        TimeOverSun = new QTimer;

        TimeOverSun->start(12000);

        connect(TimeOverSun,SIGNAL(timeout()),this,SLOT(TimeOverDelete()));

    }
    QPropertyAnimation * MS;

private slots:
    void iconChged(int){

        QTextDocument Text;

        QPixmap currFrame = _movie->currentPixmap();
        QPixmap pixmap(currFrame.width(), currFrame.height());
        pixmap.fill( Qt::transparent );
        QPainter painter( &pixmap );
        painter.drawPixmap(( pixmap.width()-currFrame.width()) / 2  ,
                           ( pixmap.height()-currFrame.height()) / 2, currFrame );
        Text.drawContents(&painter, pixmap.rect());

        setIcon(QIcon( pixmap));
        setIconSize(pixmap.rect().size());
    }

public slots:
    void MyClicked()
    {
        MSTimer = new QTimer;
        MS->stop();
        MS->setDuration(500);
        MSTimer->start(500);
        MS->setStartValue(QRect(this->pos().x() , this->pos().y() , 76 , 75));
        MS->setEndValue(QRect(0,0,76,75));
        MS->setEasingCurve(QEasingCurve::InOutCubic);
        MS->start();

        QMediaPlayer * points = new QMediaPlayer;
        points->setMedia(QUrl("points.mp3"));
        points->play();

        connect(MSTimer,SIGNAL(timeout()),this,SLOT(DeleteSun()));
    }

    void DeleteSun()
    {
        delete MSTimer;
        SunD = TRUE;
        delete this;
    }

    void TimeOverDelete()
    {
        delete TimeOverSun;
        if(SunD == FALSE)
        {
            delete this;
        }
    }

private:
    QMovie *_movie;
    QTimer * MSTimer;
    int i = 0;
    QTimer * TimeOverSun;
    bool SunD = TRUE;


};

class SunFlower : public MyGame
{
    Q_OBJECT
public:
    SunFlower(QWidget * parent = 0 , int Px = 0 , int Py = 0 , int * PS =0)
    {
        PPx = Px;
        PPy = Py;
        pp = parent;
        PPS = PS;
        S_Sun = new QMovie("SunFlower.gif");
        A = new QTimer;
        A->start(20000);
        connect(A,SIGNAL(timeout()),this,SLOT(B()));
    }

    QMovie * S_Sun;
    FlowerSun * S_FS;
    QTimer * A;
    QWidget * pp;
    int PPx = 0;
    int PPy = 0;
    int * PPS;

    int HP = 120;
public slots:
    void B()
    {
        S_FS = new FlowerSun("Sun.gif",pp,PPx,PPy);
        //connect(S_FS,SIGNAL(clicked()),this,SLOT(GetSun()));
        connect(S_FS,SIGNAL(clicked()),this,SLOT(C()));
    }

    void C()
    {
        *PPS += 25;
    }
};

class WallNut : public MyGame
{
    Q_OBJECT
public:
    WallNut(QWidget * parent = 0)
    {
        W_Wall = new QMovie("WallNut.gif");
    }

    QMovie * W_Wall;
    QTimer * A;
    int HP = 300;
};

class Peashooter : public MyGame
{
    Q_OBJECT
public:
    Peashooter(QWidget * parent = 0)
    {
        int i=0;
        for(i=0;i<10;i++)
        {
            PeaExit[i] = 0;
        }

        P = parent;

        P_Pea = new QMovie("Peashooter.gif");

        PeaTime = new QTimer;
        connect(PeaTime,SIGNAL(timeout()),this,SLOT(CreatePea()));

        CheckPea = new QTimer;
        CheckPea->start(10);
        connect(CheckPea,SIGNAL(timeout()),this,SLOT(CheckP()));
    }

    void CP()
    {
        PeaTime->start(1400);
        CPing = 1;
    }

    void DP()
    {
        PeaTime->stop();
        CPing = 0;
    }

    QMovie * P_Pea;
    QMovie * PeaM[10];
    QLabel * PeaL[10];
    QTimer * A;
    QTimer * PeaTime;
    QTimer * CheckPea;
    QWidget * P;
    QPropertyAnimation * PeaMove[10];
    QMediaPlayer * Puff;
    QMediaPlaylist * PuffList;


    int HP = 120;
    int PeaNum = 0;
    int PeaMax = 0;
    int PeaExit[10];
    int PTime[10];
    int Px = 0;
    int Py = 0;
    int CPing = 0;

public slots:
    void CreatePea()
    {
        if(PeaMax != 10)
        {
            PeaMax++;
        }
        if(PeaExit[PeaNum] == 0)
        {

            PeaL[PeaNum] = new QLabel(P);
            PeaM[PeaNum] = new QMovie("PB00.gif");
            PeaL[PeaNum]->setMovie(PeaM[PeaNum]);
            PeaL[PeaNum]->resize(56,34);
            PeaM[PeaNum]->start();
            PeaL[PeaNum]->show();
            PeaL[PeaNum]->move(Px + 10, Py + 10);

            PeaExit[PeaNum] = 1;

            Puff = new QMediaPlayer;
            PuffList = new QMediaPlaylist;
            PuffList->addMedia(QUrl("Puff.mp3"));
            Puff->setPlaylist(PuffList);
            PuffList->setCurrentIndex(1);
            Puff->play();

            PTime[PeaNum] = (900 - Px) * 3;

            PeaMove[PeaNum] = new QPropertyAnimation(PeaL[PeaNum],"geometry");
            PeaMove[PeaNum]->setDuration(PTime[PeaNum]);
            PeaMove[PeaNum]->setStartValue(QRect(Px + 10 , Py + 10 , 56 , 34));
            PeaMove[PeaNum]->setEndValue(QRect(880 , Py + 10 ,56, 34));
            PeaMove[PeaNum]->start();

            PeaNum++;
            if(PeaNum==10)
            {
                PeaNum=0;
            }
        }
    }

    void CheckP()
    {
        int i=0;

        for(i=0;i<PeaMax;i++)
        {
            if(PeaExit[i] == 1)
            {
                if(PeaL[i]->pos().x() >= 880)
                {

                    delete PeaL[i];
                    delete PeaMove[i];
                    delete PeaM[i];

                    PeaExit[i] = 0;
                }
            }
        }
    }

};

class ClassicZombie : public MyGame
{
    Q_OBJECT

public:
    ClassicZombie(QWidget * parent = 0 , int Py = 0)
    {
        CZ_Label = new QLabel(parent);
        CZ_Movie = new QMovie("Zombie.gif");
        CZ_Label->setMovie(CZ_Movie);
        CZ_Label->resize(150,150);
        CZ_Movie->start();
        CZ_Label->show();
        CZ_Label->move(850, 40 + Py*90);

        P = parent;
        PyD = Py;

        MS = new QPropertyAnimation(CZ_Label,"geometry");
        MS->setDuration(CZ_Time);
        MS->setStartValue(QRect(CZ_Label->pos().x() , CZ_Label->pos().y() , 150 , 150));
        MS->setEndValue(QRect(CZ_Label->pos().x() - 1050 , CZ_Label->pos().y() ,150, 150));
        //MS->start();

        HPCheckTimer = new QTimer;
        HPCheckTimer->start(100);
        connect(HPCheckTimer,SIGNAL(timeout()),this,SLOT(HPCheck()));

    }

    QMovie * CZ_Movie;
    QLabel * CZ_Label;
    QLabel * Head;
    QMovie * HeadM;
    QPropertyAnimation * MS;
    QTimer * HPCheckTimer;
    QTimer * DieTimer;
    QWidget * P;
    int HP = 100;
    int CZ_Time = 80000;
    int PyD;
    int State = 0;
    int HPState = 0;
    int Power = 30;

public slots:
    void HPCheck()
    {
        if(HP == 10 && HPState == 2)
        {
            CZ_Movie = new QMovie("ZombieLostHead.gif");
            CZ_Label->setMovie(CZ_Movie);
            CZ_Movie->start();
            CZ_Label->show();
            HPState = 1;

            Head = new QLabel(P);
            HeadM = new QMovie("ZombieHead.gif");
            Head->setMovie(HeadM);
            Head->resize(150,150);
            HeadM->start();
            Head->show();
            Head->move(CZ_Label->pos().x() + 60, CZ_Label->pos().y());
        }

        if(HP <= 0 && HPState == 1)
        {
            CZ_Movie = new QMovie("ZombieDie.gif");
            CZ_Label->setMovie(CZ_Movie);
            CZ_Movie->start();
            CZ_Label->show();
            MS->stop();
            State = 0;

            delete Head;

            DieTimer = new QTimer;
            DieTimer->start(2000);
            connect(DieTimer,SIGNAL(timeout()),this,SLOT(Die()));
            HPState = 0;
        }
    }

    void Die()
    {
        CZ_Movie = new QMovie("Zombie.gif");
        CZ_Label->setMovie(CZ_Movie);
        CZ_Movie->start();
        CZ_Label->show();
        CZ_Label->move(900, 40 + PyD*90);

        delete DieTimer;

        State = 0;

        HP = 100;
        HPState = -1;
    }

};

class PoleZombie : public MyGame
{
    Q_OBJECT

public:
    PoleZombie(QWidget * parent = 0, int Py = 0)
    {
        PZ_Label = new QLabel(parent);
        PZ_Movie = new QMovie("PoleVaultingZombie.gif");
        PZ_Label->setMovie(PZ_Movie);
        PZ_Label->resize(348,218);
        PZ_Movie->start();
        PZ_Label->show();
        PZ_Label->move(860 - 50, -10 + Py*95);

        P = parent;
        PyD = Py;

        MS = new QPropertyAnimation(PZ_Label,"geometry");
        MS->setDuration(40000);
        MS->setStartValue(QRect(PZ_Label->pos().x() , PZ_Label->pos().y() , 348 , 218));
        MS->setEndValue(QRect(PZ_Label->pos().x() - 1160 , PZ_Label->pos().y() ,348, 218));
        //MS->start();

        HPCheckTimer = new QTimer;
        HPCheckTimer->start(100);
        connect(HPCheckTimer,SIGNAL(timeout()),this,SLOT(HPCheck()));

    }

    void PZJump()
    {
        this->PZ_Movie = new QMovie("PoleVaultingZombieJump.gif");
        this->PZ_Label->setMovie(this->PZ_Movie);
        this->PZ_Movie->start();
        this->PZ_Label->show();
        this->MS->pause();

        JumpTimer = new QTimer;
        JumpTimer->start(1100);
        connect(JumpTimer,SIGNAL(timeout()),this,SLOT(PZJump2()));
    }

    QMovie * PZ_Movie;
    QLabel * PZ_Label;
    QTimer * JumpTimer;
    QTimer * JumpTimer2;
    QTimer * HPCheckTimer;
    QPropertyAnimation * MS;
    QWidget * P;
    QLabel * Head;
    QMovie * HeadM;
    QTimer * DieTimer;

    int Px;
    int PyD;
    int PTime;
    int PZombieCanEat=0;
    int State = 0;
    int HP = 150;
    int Power = 30;
    int PoleState = 1;
    int HPState = 2;

public slots:
    void PZJump2()
    {
        this->PZ_Label->move(PZ_Label->pos().x() - 120 , PZ_Label->pos().y());
        this->PZ_Movie = new QMovie("PoleVaultingZombieJump2.gif");
        this->PZ_Label->setMovie(this->PZ_Movie);
        this->PZ_Movie->start();
        this->PZ_Label->show();

        JumpTimer2 = new QTimer;
        JumpTimer2->start(700);
        connect(JumpTimer2,SIGNAL(timeout()),this,SLOT(PZWalk()));


        delete JumpTimer;
    }

    void PZWalk()
    {
        this->PZ_Movie = new QMovie("PoleVaultingZombieWalk.gif");
        this->PZ_Label->setMovie(this->PZ_Movie);
        this->PZ_Movie->start();
        this->PZ_Label->show();

        PoleState = 0;

        PTime = (PZ_Label->pos().x() + (PZ_Label->width()/2)) * 200;

        MS = new QPropertyAnimation(PZ_Label,"geometry");
        MS->setDuration(PTime);
        MS->setStartValue(QRect(PZ_Label->pos().x() , PZ_Label->pos().y() , 348 , 218));
        MS->setEndValue(QRect( - 300 , PZ_Label->pos().y() ,348, 218));
        MS->start();

        PZombieCanEat = 1;

        delete JumpTimer2;
    }

    void HPCheck()
    {
        if(HP == 10 && HPState == 2 && PoleState == 1)
        {
            PZ_Movie = new QMovie("PoleVaultingZombieLostHead.gif");
            PZ_Label->setMovie(PZ_Movie);
            PZ_Movie->start();
            PZ_Label->show();

            HPState = 1;

            Head = new QLabel(P);
            HeadM = new QMovie("ZombieHead.gif");
            Head->setMovie(HeadM);
            Head->resize(348,218);
            HeadM->start();
            Head->show();
            Head->move(PZ_Label->pos().x() + 180, PZ_Label->pos().y());
        }

        else if(HP == 10 && HPState == 2 && PoleState == 0)
        {
            PZ_Movie = new QMovie("PoleVaultingZombieLostHeadWalk.gif");
            PZ_Label->setMovie(PZ_Movie);
            PZ_Movie->start();
            PZ_Label->show();

            HPState = 1;

            Head = new QLabel(P);
            HeadM = new QMovie("ZombieHead.gif");
            Head->setMovie(HeadM);
            Head->resize(348,218);
            HeadM->start();
            Head->show();
            Head->move(PZ_Label->pos().x() + 180, PZ_Label->pos().y());
        }

        if(HP <= 0 && HPState == 1)
        {
            PZ_Movie = new QMovie("PoleVaultingZombieDie.gif");
            PZ_Label->setMovie(PZ_Movie);
            PZ_Movie->start();
            PZ_Label->show();
            MS->stop();
            State = 0;

            delete Head;

            DieTimer = new QTimer;
            DieTimer->start(2000);
            connect(DieTimer,SIGNAL(timeout()),this,SLOT(Die()));
            HPState = 0;
        }
    }

    void Die()
    {
        PZ_Movie = new QMovie("PoleVaultingZombie.gif");
        PZ_Label->setMovie(PZ_Movie);
        PZ_Movie->start();
        PZ_Label->show();
        PZ_Label->move(810, -10 + PyD*95);

        delete DieTimer;

        State = 0;

        HP = 150;
        HPState = -1;
        PoleState = 1;
    }
};

class BucketZombie : public MyGame
{
    Q_OBJECT

public:
    BucketZombie(QWidget * parent = 0,int Py = 0)
    {
        BZ_Label = new QLabel(parent);
        BZ_Movie = new QMovie("BucketheadZombie.gif");
        BZ_Label->setMovie(BZ_Movie);
        BZ_Label->resize(150,150);
        BZ_Movie->start();
        BZ_Label->show();
        BZ_Label->move(850, 40 + Py*90);

        P = parent;
        PyD = Py;

        MS = new QPropertyAnimation(BZ_Label,"geometry");
        MS->setDuration(75000);
        MS->setStartValue(QRect(BZ_Label->pos().x() , BZ_Label->pos().y() , 150 , 150));
        MS->setEndValue(QRect(BZ_Label->pos().x() - 1000 , BZ_Label->pos().y() ,150, 150));
        //MS->start();

        HPCheckTimer = new QTimer;
        HPCheckTimer->start(100);
        connect(HPCheckTimer,SIGNAL(timeout()),this,SLOT(HPCheck()));
    }

    QMovie * BZ_Movie;
    QLabel * BZ_Label;
    QPropertyAnimation * MS;
    QTimer * HPCheckTimer;
    QLabel * Head;
    QMovie * HeadM;
    QTimer * DieTimer;
    QWidget * P;
    int HP = 170;
    int State = 0;
    int Power = 50;
    int HPState = 0;
    int PyD = 0;

public slots:
    void HPCheck()
    {
        if(HP == 100 && HPState == 3)
        {
            BZ_Movie = new QMovie("Zombie.gif");
            BZ_Label->setMovie(BZ_Movie);
            BZ_Movie->start();
            BZ_Label->show();
            HPState = 2;

            Power = 30;
        }
        if(HP == 10 && HPState == 2)
        {
            BZ_Movie = new QMovie("ZombieLostHead.gif");
            BZ_Label->setMovie(BZ_Movie);
            BZ_Movie->start();
            BZ_Label->show();
            HPState = 1;


            Head = new QLabel(P);
            HeadM = new QMovie("ZombieHead.gif");
            Head->setMovie(HeadM);
            Head->resize(150,150);
            HeadM->start();
            Head->show();
            Head->move(BZ_Label->pos().x() + 60, BZ_Label->pos().y());
        }

        if(HP <= 0 && HPState == 1)
        {
            BZ_Movie = new QMovie("ZombieDie.gif");
            BZ_Label->setMovie(BZ_Movie);
            BZ_Movie->start();
            BZ_Label->show();
            MS->stop();
            State = 0;

            delete Head;

            DieTimer = new QTimer;
            DieTimer->start(2000);
            connect(DieTimer,SIGNAL(timeout()),this,SLOT(Die()));
            HPState = 0;
        }
    }

    void Die()
    {
        BZ_Movie = new QMovie("Zombie.gif");
        BZ_Label->setMovie(BZ_Movie);
        BZ_Movie->start();
        BZ_Label->show();
        BZ_Label->move(900, 40 + PyD*90);

        delete DieTimer;

        State = 0;

        HP = 170;
        HPState = -1;
    }
};

#endif // DZY_H
