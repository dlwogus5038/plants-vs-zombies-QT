#include "dzy.h"
#include "ui_dzy.h"
#include <QPixmap>
#include <QPushButton>
#include <QIcon>
#include <QWidget>
#include <QRegion>
#include <QPalette>
#include <QBrush>
#include <QBitmap>
#include <QIODevice>
#include <QtMultimedia/QMediaPlayer>
#include <QFile>
#include <QtMultimedia/QSound>
#include <QtMultimedia/QMediaPlaylist>
#include <QUrl>
#include <QLabel>
#include <QImage>
#include <QMainWindow>
#include <QLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QPropertyAnimation>
#include <QImage>
#include <QMessagebox>
#include <QMouseEvent>
#include <QEvent>
#include <QCursor>
#include <QPoint>
#include <QMovie>

dzy::dzy(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dzy)
{
    ui->setupUi(this);
}

void MyGame::MyBackground(void)
{
    MyStartMusic();

    setMinimumSize (900, 600);
    setMaximumSize (900, 600);

    BGlabel = new QLabel(this);
    BGlabel->setPixmap(QPixmap("surface.png"));
    BGlabel->show();

    QPixmap PM("SelectorScreenStartAdventure_32_1.png");
    QIcon normalIcon(PM);
    QPB = new QPushButton(normalIcon, tr(""), this);
    Q_CHECK_PTR(QPB);
    QPB->setIconSize(QSize(PM.width(), PM.height()));
    QPB->setGeometry(468,78,PM.width(),PM.height());
    QPB->setStyleSheet("QPushButton{border: none;}"
                       "QPushButton:hover { color: argb (0, 0, 0, 0%); }"
                       "QPushButton:pressed{border: none;}");
    QPB->resize(PM.size());
    QPalette QP(QPB->palette());
    QP.setBrush(QPalette::Button,QBrush(PM));
    QPB->setMask(PM.mask());

    PSun = &SunValueNum;



    connect(QPB,SIGNAL( pressed() ), this,SLOT(OnPressBtn()));
    connect(QPB, SIGNAL(released()), this, SLOT(OnReleaseBtn()));
    connect(QPB,SIGNAL(clicked()),this,SLOT(CountTime()));
    connect(QPB,SIGNAL(clicked()),this,SLOT(TwinkleBtn()));
    connect(QPB,SIGNAL(clicked()),this,SLOT(ZombieHand()));

}

void MyGame::CountTime()
{
    if(CountN==0)
    {
        CountN++;
        CT = new QTimer;
        CT->start(5200);

        QPAT = new QTimer;

        connect(CT,SIGNAL(timeout()),this,SLOT(HideThisW()));
        connect(CT,SIGNAL(timeout()),this,SLOT(NewGameBackG()));
        connect(CT,SIGNAL(timeout()),this,SLOT(AnimStart()));
    }
}

void MyGame::NewGameBackG()
{
    if(CountN==1)
    {
        CountN++;

        BGlabel->setPixmap(QPixmap("background1.jpg"));
        BGlabel->show();

        BGMtimer = new QTimer;
        GameBGM1 = new QMediaPlayer;
        BGMList1 = new QMediaPlaylist;
        BGMList1->addMedia(QUrl("Look up at the Sky.mp3"));
        GameBGM1->setPlaylist(BGMList1);
        BGMList1->setCurrentIndex(1);
        GameBGM1->play();
        BGMtimer->start(10000);
        connect(BGMtimer,SIGNAL(timeout()),this,SLOT(GameBGM()));

    }
}

void MyGame::QPAStart1()
{
    delete QPAT;
    QPAT1 = new QTimer;

    QPA1 = new QPropertyAnimation(BGlabel,"geometry");
    QPA1->setDuration(4000);
    QPAT1->start(4000);
    QPA1->setStartValue(QRect(0 , 0 , 1400 , 600));
    QPA1->setEndValue(QRect(-500,0,1400,600));
    QPA1->setEasingCurve(QEasingCurve::InOutCubic);
    QPA1->start();

    connect(QPAT1,SIGNAL(timeout()),this,SLOT(QPAStart2()));
}

void MyGame::QPAStart2()
{
    delete QPAT1;
    QPAT2 = new QTimer;

    QPA2 = new QPropertyAnimation(BGlabel,"geometry");
    QPA2->setDuration(4000);
    QPAT2->start(4000);
    QPA2->setStartValue(QRect(-500 , 0 , 1400 , 600));
    QPA2->setEndValue(QRect(-170,0,1400,600));
    QPA2->setEasingCurve(QEasingCurve::InOutCubic);
    QPA2->start();

    connect(QPAT2,SIGNAL(timeout()),this,SLOT(SetCard()));
}

void MyGame::GameBGM()
{
    delete BGMtimer;
    GameBGM1->stop();
    delete BGMList1;
    BGMList1 = new QMediaPlaylist;
    BGMList1->addMedia(QUrl("UraniwaNi.mp3"));
    BGMList1->addMedia(QUrl("UraniwaNi.mp3"));
    BGMList1->addMedia(QUrl("UraniwaNi.mp3"));
    BGMList1->addMedia(QUrl("UraniwaNi.mp3"));
    GameBGM1->setPlaylist(BGMList1);
    BGMList1->setCurrentIndex(1);
    GameBGM1->play();

    emit GameStart();
}

void MyGame::SetCard()
{
    delete QPAT2;

    SunLabel = new QLabel(this);
    SunLabel->setPixmap(QPixmap("SunBack.png"));
    SunLabel->move(10,-34);
    SunLabel->show();

    ShovelBack = new QLabel(this);
    ShovelBack->setPixmap(QPixmap("ShovelBack.png"));
    ShovelBack->move(485,-34);
    ShovelBack->show();

    Shovel = new QLabel(this);
    Shovel->setPixmap(QPixmap("Shovel.png"));
    Shovel->move(483,-34);
    Shovel->show();

    if(SunValueNum >= 100)
    {
        PCard1 = new QLabel(this);
        PCard1->setPixmap(QPixmap("Peashooter1.png"));
        PCard1->move(143,-60);
        PCard1->show();

        PCard2 = new QLabel(this);
        PCard2->setPixmap(QPixmap("SunFlower1.png"));
        PCard2->move(253,-60);
        PCard2->show();

        PCard3 = new QLabel(this);
        PCard3->setPixmap(QPixmap("WallNut1.png"));
        PCard3->move(363,-60);
        PCard3->show();
    }

    else if(SunValueNum < 100 && SunValueNum >=50)
    {
        PCard1 = new QLabel(this);
        PCard1->setPixmap(QPixmap("Peashooter2.png"));
        PCard1->move(143,-60);
        PCard1->show();

        PCard2 = new QLabel(this);
        PCard2->setPixmap(QPixmap("SunFlower1.png"));
        PCard2->move(253,-60);
        PCard2->show();

        PCard3 = new QLabel(this);
        PCard3->setPixmap(QPixmap("WallNut1.png"));
        PCard3->move(363,-60);
        PCard3->show();
    }

    else if(SunValueNum < 50)
    {
        PCard1 = new QLabel(this);
        PCard1->setPixmap(QPixmap("Peashooter2.png"));
        PCard1->move(143,-60);
        PCard1->show();

        PCard2 = new QLabel(this);
        PCard2->setPixmap(QPixmap("SunFlower2.png"));
        PCard2->move(253,-60);
        PCard2->show();

        PCard3 = new QLabel(this);
        PCard3->setPixmap(QPixmap("WallNut2.png"));
        PCard3->move(363,-60);
        PCard3->show();
    }
}

void MyGame::MoveCard()
{
    int i = 0;

    MoveS1 = new QPropertyAnimation(SunLabel,"geometry");
    MoveS1->setDuration(1000);
    MoveS1->setStartValue(QRect(10 , -34 , 123 , 34));
    MoveS1->setEndValue(QRect(10,10,123,34));
    MoveS1->setEasingCurve(QEasingCurve::InOutCubic);
    MoveS1->start();

    MoveSH = new QPropertyAnimation(Shovel,"geometry");
    MoveSH->setDuration(1000);
    MoveSH->setStartValue(QRect(485 , -34 , 76 , 34));
    MoveSH->setEndValue(QRect(485,20,76,34));
    MoveSH->setEasingCurve(QEasingCurve::InOutCubic);
    MoveSH->start();

    MoveSHB = new QPropertyAnimation(ShovelBack,"geometry");
    MoveSHB->setDuration(1000);
    MoveSHB->setStartValue(QRect(483 , -34 , 76 , 34));
    MoveSHB->setEndValue(QRect(483,20,76,34));
    MoveSHB->setEasingCurve(QEasingCurve::InOutCubic);
    MoveSHB->start();

    SunValueLabel = new QLabel(this);
    SunValueLabel->setStyleSheet("font-size:24px");
    SunValueLabel->setGeometry(65,16,100,20);
    SunString = QString("%1").arg(SunValueNum);
    SunValueLabel->setText(SunString);
    SunValueLabel->show();

    MoveC1 = new QPropertyAnimation(PCard1,"geometry");
    MoveC1->setDuration(1000);
    MoveC1->setStartValue(QRect(143 , -60 , 100 , 60));
    MoveC1->setEndValue(QRect(143,5,100,60));
    MoveC1->setEasingCurve(QEasingCurve::InOutCubic);
    MoveC1->start();

    QString PP;
    PeaPrice = new QLabel(this);
    PP = QString("%1").arg(PeaPriceNum);
    PeaPrice->setText(PP);
    PeaPrice->move(215,50);
    PeaPrice->show();

    MoveC2 = new QPropertyAnimation(PCard2,"geometry");
    MoveC2->setDuration(1000);
    MoveC2->setStartValue(QRect(253 , -60 , 100 , 60));
    MoveC2->setEndValue(QRect(253,5,100,60));
    MoveC2->setEasingCurve(QEasingCurve::InOutCubic);
    MoveC2->start();

    QString SP;
    SunPrice = new QLabel(this);
    SP = QString("%1").arg(SunPriceNum);
    SunPrice->setText(SP);
    SunPrice->move(330,50);
    SunPrice->show();

    MoveC3 = new QPropertyAnimation(PCard3,"geometry");
    MoveC3->setDuration(1000);
    MoveC3->setStartValue(QRect(363 , -60 , 100 , 60));
    MoveC3->setEndValue(QRect(363,5,100,60));
    MoveC3->setEasingCurve(QEasingCurve::InOutCubic);
    MoveC3->start();

    QString WP;
    WallPrice = new QLabel(this);
    WP = QString("%1").arg(WallPriceNum);
    WallPrice->setText(WP);
    WallPrice->move(440,50);
    WallPrice->show();

    emit SetMyBox();

    SSTimer = new QTimer;
    SSTimer->start(7000);
    connect(SSTimer,SIGNAL(timeout()),this,SLOT(SetSun()));

    CanCS = TRUE;

    //

    for(i=0;i<5;i++)
    {
        CZombie[i] = new ClassicZombie(this,i);
        CZombieEat[i] = 0;

        BZombie[i] = new BucketZombie(this,i);
        BZombieEat[i] = 0;

        PZombie[i] = new PoleZombie(this,i);
        PZombieEat[i] = 0;
    }

    CBZTimer = new QTimer;
    CBZTimer->start(30000);
    connect(CBZTimer,SIGNAL(timeout()),this,SLOT(CreateBZ()));

    BEatP = new QTimer;
    BEatP->start(1000);
    connect(BEatP,SIGNAL(timeout()),this,SLOT(BCheckP()));

    //

    CCZTimer = new QTimer;
    CCZTimer->start(15000);
    connect(CCZTimer,SIGNAL(timeout()),this,SLOT(CreateCZ()));

    CEatP = new QTimer;
    CEatP->start(1000);
    connect(CEatP,SIGNAL(timeout()),this,SLOT(CCheckP()));

    //

    CPZTimer = new QTimer;
    CPZTimer->start(40000);
    connect(CPZTimer,SIGNAL(timeout()),this,SLOT(CreatePZ()));

    PEatP = new QTimer;
    PEatP->start(1000);
    connect(PEatP,SIGNAL(timeout()),this,SLOT(PCheckP()));

    //

    CheckPeaZombie = new QTimer;
    CheckPeaZombie->start(10);
    connect(CheckPeaZombie,SIGNAL(timeout()),this,SLOT(CheckPZ()));

    //

    QTimer * SSV = new QTimer;
    SSV->start(100);
    connect(SSV,SIGNAL(timeout()),this,SLOT(SSVS()));
}

void MyGame::CheckAllDie(int j)
{
    if(CZombie[j]->HPState == -1)
    {
        DieNumber++;
        CZombie[j]->HPState = 0;
    }
    if(BZombie[j]->HPState == -1)
    {
        DieNumber++;
        BZombie[j]->HPState = 0;
    }
    if(PZombie[j]->HPState == -1)
    {
        DieNumber++;
        PZombie[j]->HPState = 0;
    }

    if(DieNumber == ZombieNumber)
    {
        emit Victory();
        ZombieNumber++;
    }
}

void MyGame::CheckFail(int j)
{
    if(Fail == FALSE)
    {
        if(CZombie[j]->CZ_Label->pos().x() <= -180)
        {
            emit FailSlot();
            Fail = TRUE;
        }
        else if(BZombie[j]->BZ_Label->pos().x() <= -130)
        {
            emit FailSlot();
            Fail = TRUE;
        }
        else if(PZombie[j]->PZ_Label->pos().x() <= -280)
        {
            emit FailSlot();
            Fail = TRUE;
        }
    }
}

void MyGame::CheckPZ()
{
    int i=0;
    int j=0;
    int k=0;

    for(i=0;i<9;i++)
    {
        for(j=0;j<5;j++)
        {


            CheckAllDie(j);
            CheckFail(j);


            if(MyBoxState[i][j] == 1 &&
                    ( CZombie[j]->State == 1 || BZombie[j]->State == 1 || PZombie[j]->State == 1)
                    && PS[i][j]->CPing == 0
                    && ((CZombie[j]->CZ_Label->pos().x() >= MyBox[i][j]->pos().x() && CZombie[j]->State == 1)
                    ||(BZombie[j]->BZ_Label->pos().x() >= MyBox[i][j]->pos().x() && BZombie[j]->State == 1)
                        || (PZombie[j]->PZ_Label->pos().x() >= MyBox[i][j]->pos().x() && PZombie[j]->State == 1)))
            {
                PS[i][j]->CP();
            }
            else if(MyBoxState[i][j] == 1 && CZombie[j]->State == 0 && PS[i][j]->CPing == 1
                    && BZombie[j]->State == 0
                    && PZombie[j]->State == 0
                    ||(CZombie[j]->CZ_Label->pos().x() <= MyBox[i][j]->pos().x() && BZombie[j]->BZ_Label->pos().x() <= MyBox[i][j]->pos().x()
                       && PZombie[j]->PZ_Label->pos().x() <= MyBox[i][j]->pos().x()))
            {
                PS[i][j]->DP();
            }

            //


            if(MyBoxState[i][j] == 1)
            {
                for( k=0 ; k<PS[i][j]->PeaMax ; k++ )
                {

                    if(CZombie[j]->State == 1
                            && PS[i][j]->PeaExit[k] == 1
                            && PS[i][j]->PeaL[k]->pos().x() >= CZombie[j]->CZ_Label->pos().x() + 40
                            && PS[i][j]->PeaL[k]->pos().x() <= CZombie[j]->CZ_Label->pos().x() + 40 + CZombie[j]->CZ_Label->width())
                    {
                        PeaShoot = new QMediaPlayer;
                        PeaShootList = new QMediaPlaylist;
                        PeaShootList->addMedia(QUrl("splat1.mp3"));
                        PeaShoot->setPlaylist(PeaShootList);
                        PeaShootList->setCurrentIndex(1);
                        PeaShoot->play();

                        delete PS[i][j]->PeaL[k];
                        PS[i][j]->PeaExit[k] = 0;
                        CZombie[j]->HP -= 10;
                    }

                    if(BZombie[j]->State == 1
                            && PS[i][j]->PeaExit[k] == 1
                            && PS[i][j]->PeaL[k]->pos().x() >= BZombie[j]->BZ_Label->pos().x() + 40
                            && PS[i][j]->PeaL[k]->pos().x() <= BZombie[j]->BZ_Label->pos().x() + 40 + BZombie[j]->BZ_Label->width())
                    {
                        PeaShoot = new QMediaPlayer;
                        PeaShootList = new QMediaPlaylist;
                        PeaShootList->addMedia(QUrl("splat1.mp3"));
                        PeaShoot->setPlaylist(PeaShootList);
                        PeaShootList->setCurrentIndex(1);
                        PeaShoot->play();

                        delete PS[i][j]->PeaL[k];
                        PS[i][j]->PeaExit[k] = 0;
                        BZombie[j]->HP -= 10;
                    }

                    if(PZombie[j]->State == 1
                            && PS[i][j]->PeaExit[k] == 1
                            && PS[i][j]->PeaL[k]->pos().x() >= PZombie[j]->PZ_Label->pos().x() + 175
                            && PS[i][j]->PeaL[k]->pos().x() <= PZombie[j]->PZ_Label->pos().x() + 175 + 40)
                    {
                        PeaShoot = new QMediaPlayer;
                        PeaShootList = new QMediaPlaylist;
                        PeaShootList->addMedia(QUrl("splat1.mp3"));
                        PeaShoot->setPlaylist(PeaShootList);
                        PeaShootList->setCurrentIndex(1);
                        PeaShoot->play();

                        delete PS[i][j]->PeaL[k];
                        PS[i][j]->PeaExit[k] = 0;
                        PZombie[j]->HP -= 10;
                    }
                }
            }
        }
    }
}

void MyGame::CreateCZ()
{
    if(CZNum == 0 )
    {
        CZombie[0]->MS->start();
        CZombie[0]->State = 1;
        CZombie[0]->HPState = 2;
        CZNum++;

        QMediaPlayer * CZ = new QMediaPlayer;
        QMediaPlaylist * CZL = new QMediaPlaylist;
        CZL->addMedia(QUrl("awooga.mp3"));
        CZ->setPlaylist(CZL);
        CZL->setCurrentIndex(1);
        CZ->play();
    }
    else if(CZNum ==1 )
    {
        CZombie[3]->MS->start();
        CZombie[3]->State = 1;
        CZombie[3]->HPState = 2;
        CZNum++;
    }
    else if(CZNum ==2 )
    {
        CZombie[1]->MS->start();
        CZombie[1]->State = 1;
        CZombie[1]->HPState = 2;
        CZNum++;
    }
    else if(CZNum ==3 )
    {
        CZombie[4]->MS->start();
        CZombie[4]->State = 1;
        CZombie[4]->HPState = 2;
        CZNum++;
    }
    else if(CZNum ==4 )
    {
        CZombie[2]->MS->start();
        CZombie[2]->State = 1;
        CZombie[2]->HPState = 2;
        CZNum++;
        delete CCZTimer;
    }
    else if(CZNum == 5 )
    {
        delete CCZTimer;
    }
}

void MyGame::CreateBZ()
{
    if(BZNum == 0 )
    {
        BZombie[0]->MS->start();
        BZombie[0]->State = 1;
        BZombie[0]->HPState = 3;
        BZNum++;
    }
    else if(BZNum ==1 )
    {
        BZombie[3]->MS->start();
        BZombie[3]->State = 1;
        BZombie[3]->HPState = 3;
        BZNum++;
    }
    else if(BZNum ==2 )
    {
        BZombie[1]->MS->start();
        BZombie[1]->State = 1;
        BZombie[1]->HPState = 3;
        BZNum++;
    }
    else if(BZNum == 3 )
    {
        delete CBZTimer;
    }
}

void MyGame::CreatePZ()
{

    if(PZNum == 0 )
    {
        PZombie[4]->MS->start();
        PZombie[4]->State = 1;
        PZombie[4]->HPState = 2;
        PZNum++;
    }
    else if(PZNum ==1 )
    {
        PZombie[1]->MS->start();
        PZombie[1]->State = 1;
        PZombie[1]->HPState = 2;
        PZNum++;
    }
    else if(PZNum ==2 )
    {
        PZombie[2]->MS->start();
        PZombie[2]->State = 1;
        PZombie[2]->HPState = 2;
        PZNum++;
    }
    else if(PZNum == 3 )
    {
        delete CPZTimer;
    }

}

void MyGame::CCheckP()
{
    int i=0;
    int k=0;

    for(k=0;k<5;k++)
    {
        for(i=0;i<9;i++)
        {

            if(CZombie[k]->CZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && CZombie[k]->CZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && CZombieEat[k] == 0
                    && CZombie[k]->HPState==2)
            {
                CZombie[k]->CZ_Movie = new QMovie("ZombieAttack.gif");
                CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
                CZombie[k]->CZ_Movie->start();
                CZombie[k]->CZ_Label->show();
                CZombie[k]->MS->pause();

                CEP[k] = new QMediaPlayer;
                CEPList[k] = new QMediaPlaylist;
                CEPList[k]->addMedia(QUrl("chompsoft.mp3"));
                CEPList[k]->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                CEP[k]->setPlaylist(CEPList[k]);
                CEPList[k]->setCurrentIndex(1);
                CEP[k]->play();

                CZombieEat[k]++;
            }

            else if(CZombie[k]->CZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && CZombie[k]->CZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && CZombieEat[k] == 1
                    && CZombie[k]->HPState==2)
            {
                CDeleteP(i,k);
            }

            else if(CZombie[k]->CZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && CZombie[k]->CZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] == 0)
                    && CZombieEat[k] == 1
                    && CZombie[k]->HPState==2)
            {
                CEP[k]->stop();
                delete CEPList[k];
                CEPList[k] = new QMediaPlaylist;
                CEPList[k]->addMedia(QUrl("chomp.mp3"));
                CEP[k]->setPlaylist(CEPList[k]);
                CEP[k]->play();

                CZombie[k]->CZ_Movie = new QMovie("Zombie.gif");
                CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
                CZombie[k]->CZ_Movie->start();
                CZombie[k]->CZ_Label->show();
                CZombie[k]->MS->resume();
                CZombieEat[k] = 0;
            }

        //=========================================================================================

            else if(CZombie[k]->CZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && CZombie[k]->CZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && CZombieEat[k] == 0
                    && CZombie[k]->HPState==1)
            {
                CZombie[k]->CZ_Movie = new QMovie("ZombieLostHeadAttack.gif");
                CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
                CZombie[k]->CZ_Movie->start();
                CZombie[k]->CZ_Label->show();
                CZombie[k]->MS->pause();

                CEP[k] = new QMediaPlayer;
                CEPList[k] = new QMediaPlaylist;
                CEPList[k]->addMedia(QUrl("chompsoft.mp3"));
                CEPList[k]->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                CEP[k]->setPlaylist(CEPList[k]);
                CEPList[k]->setCurrentIndex(1);
                CEP[k]->play();

                CZombieEat[k]++;
            }

            else if(CZombie[k]->CZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && CZombie[k]->CZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && CZombieEat[k] == 1
                    && CZombie[k]->HPState==1)
            {

                if(CEating == 0)
                {
                    CZombie[k]->CZ_Movie = new QMovie("ZombieLostHeadAttack.gif");
                    CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
                    CZombie[k]->CZ_Movie->start();
                    CZombie[k]->CZ_Label->show();
                    CEating++;
                }
                CDeleteP(i,k);
            }

            else if(CZombie[k]->CZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && CZombie[k]->CZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] == 0)
                    && CZombieEat[k] == 1
                    && CZombie[k]->HPState==1)
            {
                CEP[k]->stop();
                delete CEPList[k];
                CEPList[k] = new QMediaPlaylist;
                CEPList[k]->addMedia(QUrl("chomp.mp3"));
                CEP[k]->setPlaylist(CEPList[k]);
                CEP[k]->play();

                CZombie[k]->CZ_Movie = new QMovie("ZombieLostHead.gif");
                CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
                CZombie[k]->CZ_Movie->start();
                CZombie[k]->CZ_Label->show();
                CZombie[k]->MS->resume();
                CZombieEat[k] = 0;
            }

        //==============================================================================

            if(CZombie[k]->CZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                && CZombie[k]->CZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                && CZombieEat[k] == 1
                && CZombie[k]->HPState==0)
            {
                CEP[k]->stop();
                CEPList[k] = new QMediaPlaylist;
                CEPList[k]->addMedia(QUrl(""));
                CEP[k]->setPlaylist(CEPList[k]);
                CEP[k]->play();

                CZombieEat[k] = 0;
            }

        }
    }
}

void MyGame::BCheckP()
{
    int i=0;
    int k=0;

    for(k=0;k<5;k++)
    {
        for(i=0;i<9;i++)
        {

            if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && BZombieEat[k] == 0
                    && BZombie[k]->HPState==3)
            {
                BZombie[k]->BZ_Movie = new QMovie("BucketheadZombieAttack.gif");
                BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
                BZombie[k]->BZ_Movie->start();
                BZombie[k]->BZ_Label->show();
                BZombie[k]->MS->pause();

                BEP[k] = new QMediaPlayer;
                BEPList[k] = new QMediaPlaylist;
                BEPList[k]->addMedia(QUrl("chompsoft.mp3"));
                BEPList[k]->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                BEP[k]->setPlaylist(BEPList[k]);
                BEPList[k]->setCurrentIndex(1);
                BEP[k]->play();

                BZombieEat[k]++;
            }

            else if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && BZombieEat[k] == 1
                    && BZombie[k]->HPState==3)
            {
                BDeleteP(i,k);
            }

            else if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] == 0)
                    && BZombieEat[k] == 1
                    && BZombie[k]->HPState==3)
            {
                BEP[k]->stop();
                delete BEPList[k];
                BEPList[k] = new QMediaPlaylist;
                BEPList[k]->addMedia(QUrl("chomp.mp3"));
                BEP[k]->setPlaylist(BEPList[k]);
                BEP[k]->play();

                BZombie[k]->BZ_Movie = new QMovie("BucketheadZombie.gif");
                BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
                BZombie[k]->BZ_Movie->start();
                BZombie[k]->BZ_Label->show();
                BZombie[k]->MS->resume();
                BZombieEat[k] = 0;
            }

        //=====================================================================

            else if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && BZombieEat[k] == 0
                    && BZombie[k]->HPState==2)
            {
                BZombie[k]->BZ_Movie = new QMovie("ZombieAttack.gif");
                BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
                BZombie[k]->BZ_Movie->start();
                BZombie[k]->BZ_Label->show();
                BZombie[k]->MS->pause();

                BEP[k] = new QMediaPlayer;
                BEPList[k] = new QMediaPlaylist;
                BEPList[k]->addMedia(QUrl("chompsoft.mp3"));
                BEPList[k]->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                BEP[k]->setPlaylist(BEPList[k]);
                BEPList[k]->setCurrentIndex(1);
                BEP[k]->play();

                BZombieEat[k]++;
            }

            else if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && BZombieEat[k] == 1
                    && BZombie[k]->HPState==2)
            {
                if(BEating == 0)
                {
                    BZombie[k]->BZ_Movie = new QMovie("ZombieAttack.gif");
                    BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
                    BZombie[k]->BZ_Movie->start();
                    BZombie[k]->BZ_Label->show();
                    BEating ++;
                }
                BDeleteP(i,k);
            }

            else if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] == 0)
                    && BZombieEat[k] == 1
                    && BZombie[k]->HPState==2)
            {
                BEP[k]->stop();
                delete BEPList[k];
                BEPList[k] = new QMediaPlaylist;
                BEPList[k]->addMedia(QUrl("chomp.mp3"));
                BEP[k]->setPlaylist(BEPList[k]);
                BEP[k]->play();

                BZombie[k]->BZ_Movie = new QMovie("Zombie.gif");
                BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
                BZombie[k]->BZ_Movie->start();
                BZombie[k]->BZ_Label->show();
                BZombie[k]->MS->resume();
                BZombieEat[k] = 0;
            }

        //=================================================

            else if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && BZombieEat[k] == 0
                    && BZombie[k]->HPState==1)
            {
                BZombie[k]->BZ_Movie = new QMovie("ZombieLostHeadAttack.gif");
                BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
                BZombie[k]->BZ_Movie->start();
                BZombie[k]->BZ_Label->show();
                BZombie[k]->MS->pause();

                BEP[k] = new QMediaPlayer;
                BEPList[k] = new QMediaPlaylist;
                BEPList[k]->addMedia(QUrl("chompsoft.mp3"));
                BEPList[k]->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                BEP[k]->setPlaylist(BEPList[k]);
                BEPList[k]->setCurrentIndex(1);
                BEP[k]->play();

                BZombieEat[k]++;
            }

            else if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] != 0)
                    && BZombieEat[k] == 1
                    && BZombie[k]->HPState==1)
            {
                if(BEating == 1)
                {
                    BZombie[k]->BZ_Movie = new QMovie("ZombieLostHeadAttack.gif");
                    BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
                    BZombie[k]->BZ_Movie->start();
                    BZombie[k]->BZ_Label->show();
                    BEating ++;
                }
                BDeleteP(i,k);
            }

            else if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    &&(MyBoxState[i][k] == 0)
                    && BZombieEat[k] == 1
                    && BZombie[k]->HPState==1)
            {
                BEP[k]->stop();
                delete BEPList[k];
                BEPList[k] = new QMediaPlaylist;
                BEPList[k]->addMedia(QUrl("chomp.mp3"));
                BEP[k]->setPlaylist(BEPList[k]);
                BEP[k]->play();

                BZombie[k]->BZ_Movie = new QMovie("ZombieLostHead.gif");
                BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
                BZombie[k]->BZ_Movie->start();
                BZombie[k]->BZ_Label->show();
                BZombie[k]->MS->resume();
                BZombieEat[k] = 0;
            }


            if(BZombie[k]->BZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 95
                    && BZombie[k]->BZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 95
                    && BZombieEat[k] == 1
                    && BZombie[k]->HPState==0)
            {
                BEP[k]->stop();
                BEPList[k] = new QMediaPlaylist;
                BEPList[k]->addMedia(QUrl(""));
                BEP[k]->setPlaylist(BEPList[k]);
                BEP[k]->play();

                BZombieEat[k] = 0;
            }


        }
    }
}

void MyGame::PCheckP()
{
    int i=0;
    int k=0;

    for(k=0;k<5;k++)
    {
        for(i=0;i<9;i++)
        {

            if(PZombie[k]->PZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 200
                    && PZombie[k]->PZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 200
                    &&(MyBoxState[i][k] != 0)
                    && PZombieEat[k] == 0
                    && PZombie[k]->PZombieCanEat == 0
                    && PZombie[k]->PoleState == 1
                    && PZombie[k]->HPState == 2)
            {
                PZombie[k]->PZJump();

                PZombieEat[k]++;
            }

            else if(PZombie[k]->PZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 200
                    && PZombie[k]->PZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 200
                    &&(MyBoxState[i][k] != 0)
                    && PZombieEat[k] == 1
                    && PZombie[k]->PZombieCanEat == 1
                    && PZombie[k]->HPState == 2)
            {
                PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieAttack.gif");
                PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
                PZombie[k]->PZ_Movie->start();
                PZombie[k]->PZ_Label->show();
                PZombie[k]->MS->pause();

                PEP[k] = new QMediaPlayer;
                PEPList[k] = new QMediaPlaylist;
                PEPList[k]->addMedia(QUrl("chompsoft.mp3"));
                PEPList[k]->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                PEP[k]->setPlaylist(PEPList[k]);
                PEPList[k]->setCurrentIndex(1);
                PEP[k]->play();
                PZombieEat[k]++;
            }

            else if(PZombie[k]->PZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 200
                    && PZombie[k]->PZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 200
                    &&(MyBoxState[i][k] != 0)
                    && PZombieEat[k] == 2
                    && PZombie[k]->PZombieCanEat == 1
                    && PZombie[k]->HPState == 2)
            {
                PDeleteP(i,k);
            }

            else if(PZombie[k]->PZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 200
                    && PZombie[k]->PZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 200
                    &&(MyBoxState[i][k] == 0)
                    && PZombieEat[k] == 2
                    && PZombie[k]->PZombieCanEat == 1
                    && PZombie[k]->HPState == 2)
            {
                PEP[k]->stop();
                delete PEPList[k];
                PEPList[k] = new QMediaPlaylist;
                PEPList[k]->addMedia(QUrl("chomp.mp3"));
                PEP[k]->setPlaylist(PEPList[k]);
                PEP[k]->play();

                PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieWalk.gif");
                PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
                PZombie[k]->PZ_Movie->start();
                PZombie[k]->PZ_Label->show();
                PZombie[k]->MS->resume();
                PZombieEat[k] = 1;
            }

        //==================================================================================


            else if(PZombie[k]->PZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 200
                    && PZombie[k]->PZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 200
                    &&(MyBoxState[i][k] != 0)
                    && PZombieEat[k] == 1
                    && PZombie[k]->PZombieCanEat == 1
                    && PZombie[k]->HPState == 1)
            {
                PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieLostHeadAttack.gif");
                PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
                PZombie[k]->PZ_Movie->start();
                PZombie[k]->PZ_Label->show();
                PZombie[k]->MS->pause();

                PEP[k] = new QMediaPlayer;
                PEPList[k] = new QMediaPlaylist;
                PEPList[k]->addMedia(QUrl("chompsoft.mp3"));
                PEPList[k]->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                PEP[k]->setPlaylist(PEPList[k]);
                PEPList[k]->setCurrentIndex(1);
                PEP[k]->play();
                PZombieEat[k]++;
            }

            else if(PZombie[k]->PZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 200
                    && PZombie[k]->PZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 200
                    &&(MyBoxState[i][k] != 0)
                    && PZombieEat[k] == 2
                    && PZombie[k]->PZombieCanEat == 1
                    && PZombie[k]->HPState == 1)
            {
                if(PEating == 0)
                {
                    PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieLostHeadAttack.gif");
                    PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
                    PZombie[k]->PZ_Movie->start();
                    PZombie[k]->PZ_Label->show();
                    PEating ++;
                }
                PDeleteP(i,k);
            }

            else if(PZombie[k]->PZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 200
                    && PZombie[k]->PZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 200
                    &&(MyBoxState[i][k] == 0)
                    && PZombieEat[k] == 2
                    && PZombie[k]->PZombieCanEat == 1
                    && PZombie[k]->HPState == 1)
            {
                PEP[k]->stop();
                delete PEPList[k];
                PEPList[k] = new QMediaPlaylist;
                PEPList[k]->addMedia(QUrl("chomp.mp3"));
                PEP[k]->setPlaylist(PEPList[k]);
                PEP[k]->play();

                PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieLostHeadWalk.gif");
                PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
                PZombie[k]->PZ_Movie->start();
                PZombie[k]->PZ_Label->show();
                PZombie[k]->MS->resume();
                PZombieEat[k] = 1;
            }

                //===================================================

            if(PZombie[k]->PZ_Label->pos().x() <= MyBox[i][k]->pos().x() + MyBox[i][k]->width() - 200
                    && PZombie[k]->PZ_Label->pos().x() >= MyBox[i][k]->pos().x() - 200
                    && PZombieEat[k] == 2
                    && PZombie[k]->HPState==0)
            {
                PEP[k]->stop();
                PEPList[k] = new QMediaPlaylist;
                PEPList[k]->addMedia(QUrl(""));
                PEP[k]->setPlaylist(PEPList[k]);
                PEP[k]->play();

                PZombieEat[k] = 0;
            }
        }
    }
}

void MyGame::CDeleteP(int CZ_i,int k)
{


    if(MyBoxState[CZ_i][k] == 1 && CZombie[k]->HPState == 2)
    {
        if(PS[CZ_i][k]->HP > 0)
        {
            PS[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(PS[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

            delete PS[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            CZombieEat[k]=0;

            CEP[k]->stop();
            delete CEPList[k];
            CEPList[k] = new QMediaPlaylist;
            CEPList[k]->addMedia(QUrl("chomp.mp3"));
            CEP[k]->setPlaylist(CEPList[k]);
            CEP[k]->play();

            CZombie[k]->CZ_Movie = new QMovie("Zombie.gif");
            CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
            CZombie[k]->CZ_Movie->start();
            CZombie[k]->CZ_Label->show();
            CZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 2 && CZombie[k]->HPState == 2)
    {
        if(SF[CZ_i][k]->HP > 0)
        {
            SF[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(SF[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete SF[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            CZombieEat[k]=0;

            CEP[k]->stop();
            delete CEPList[k];
            CEPList[k] = new QMediaPlaylist;
            CEPList[k]->addMedia(QUrl("chomp.mp3"));
            CEP[k]->setPlaylist(CEPList[k]);
            CEP[k]->play();

            CZombie[k]->CZ_Movie = new QMovie("Zombie.gif");
            CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
            CZombie[k]->CZ_Movie->start();
            CZombie[k]->CZ_Label->show();
            CZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 3 && CZombie[k]->HPState == 2)
    {
        if(WN[CZ_i][k]->HP > 210)
        {
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <=210 && WN[CZ_i][k]->HP >= 170)
        {
            QMovie * movie= new QMovie("WallNut_cracked1.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 170 && WN[CZ_i][k]->HP > 110)
        {
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 110 && WN[CZ_i][k]->HP >= 70)
        {
            QMovie * movie= new QMovie("WallNut_cracked2.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 70 && WN[CZ_i][k]->HP > 0)
        {
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete WN[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            CZombieEat[k]=0;

            CEP[k]->stop();
            delete CEPList[k];
            CEPList[k] = new QMediaPlaylist;
            CEPList[k]->addMedia(QUrl("chomp.mp3"));
            CEP[k]->setPlaylist(CEPList[k]);
            CEP[k]->play();

            CZombie[k]->CZ_Movie = new QMovie("Zombie.gif");
            CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
            CZombie[k]->CZ_Movie->start();
            CZombie[k]->CZ_Label->show();
            CZombie[k]->MS->resume();

        }
    }

    //================================================

    else if(MyBoxState[CZ_i][k] == 1 && CZombie[k]->HPState == 1)
    {
        if(PS[CZ_i][k]->HP > 0)
        {
            PS[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(PS[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

            delete PS[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            CZombieEat[k]=0;

            CEP[k]->stop();
            delete CEPList[k];
            CEPList[k] = new QMediaPlaylist;
            CEPList[k]->addMedia(QUrl("chomp.mp3"));
            CEP[k]->setPlaylist(CEPList[k]);
            CEP[k]->play();

            CZombie[k]->CZ_Movie = new QMovie("ZombieLostHead.gif");
            CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
            CZombie[k]->CZ_Movie->start();
            CZombie[k]->CZ_Label->show();
            CZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 2 && CZombie[k]->HPState == 1)
    {
        if(SF[CZ_i][k]->HP > 0)
        {
            SF[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(SF[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete SF[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            CZombieEat[k]=0;

            CEP[k]->stop();
            delete CEPList[k];
            CEPList[k] = new QMediaPlaylist;
            CEPList[k]->addMedia(QUrl("chomp.mp3"));
            CEP[k]->setPlaylist(CEPList[k]);
            CEP[k]->play();

            CZombie[k]->CZ_Movie = new QMovie("ZombieLostHead.gif");
            CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
            CZombie[k]->CZ_Movie->start();
            CZombie[k]->CZ_Label->show();
            CZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 3 && CZombie[k]->HPState == 1)
    {
        if(WN[CZ_i][k]->HP > 210)
        {
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <=210 && WN[CZ_i][k]->HP >= 170)
        {
            QMovie * movie= new QMovie("WallNut_cracked1.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 170 && WN[CZ_i][k]->HP > 110)
        {
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 110 && WN[CZ_i][k]->HP >= 70)
        {
            QMovie * movie= new QMovie("WallNut_cracked2.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 70 && WN[CZ_i][k]->HP > 0)
        {
            WN[CZ_i][k]->HP -= CZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete WN[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            CZombieEat[k]=0;

            CEP[k]->stop();
            delete CEPList[k];
            CEPList[k] = new QMediaPlaylist;
            CEPList[k]->addMedia(QUrl("chomp.mp3"));
            CEP[k]->setPlaylist(CEPList[k]);
            CEP[k]->play();

            CZombie[k]->CZ_Movie = new QMovie("ZombieLostHead.gif");
            CZombie[k]->CZ_Label->setMovie(CZombie[k]->CZ_Movie);
            CZombie[k]->CZ_Movie->start();
            CZombie[k]->CZ_Label->show();
            CZombie[k]->MS->resume();

        }
    }
}

void MyGame::BDeleteP(int CZ_i,int k)
{


    if(MyBoxState[CZ_i][k] == 1  && BZombie[k]->HPState==3)
    {
        if(PS[CZ_i][k]->HP > 0)
        {
            PS[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(PS[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete PS[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            BZombieEat[k]=0;

            BEP[k]->stop();
            delete BEPList[k];
            BEPList[k] = new QMediaPlaylist;
            BEPList[k]->addMedia(QUrl("chomp.mp3"));
            BEP[k]->setPlaylist(CEPList[k]);
            BEP[k]->play();

            BZombie[k]->BZ_Movie = new QMovie("BucketheadZombie.gif");
            BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
            BZombie[k]->BZ_Movie->start();
            BZombie[k]->BZ_Label->show();
            BZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 2 && BZombie[k]->HPState==3)
    {
        if(SF[CZ_i][k]->HP > 0)
        {
            SF[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(SF[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete SF[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            BZombieEat[k]=0;

            BEP[k]->stop();
            delete BEPList[k];
            BEPList[k] = new QMediaPlaylist;
            BEPList[k]->addMedia(QUrl("chomp.mp3"));
            BEP[k]->setPlaylist(BEPList[k]);
            BEP[k]->play();

            BZombie[k]->BZ_Movie = new QMovie("BucketheadZombie.gif");
            BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
            BZombie[k]->BZ_Movie->start();
            BZombie[k]->BZ_Label->show();
            BZombie[k]->MS->resume();
        }
    }

    else if(MyBoxState[CZ_i][k] == 3 && BZombie[k]->HPState==3)
    {
        if(WN[CZ_i][k]->HP > 210)
        {
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <=210 && WN[CZ_i][k]->HP >= 170)
        {
            QMovie * movie= new QMovie("WallNut_cracked1.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 170 && WN[CZ_i][k]->HP > 110)
        {
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 110 && WN[CZ_i][k]->HP >= 70)
        {
            QMovie * movie= new QMovie("WallNut_cracked2.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 70 && WN[CZ_i][k]->HP > 0)
        {
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete WN[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            BZombieEat[k]=0;

            BEP[k]->stop();
            delete BEPList[k];
            BEPList[k] = new QMediaPlaylist;
            BEPList[k]->addMedia(QUrl("chomp.mp3"));
            BEP[k]->setPlaylist(BEPList[k]);
            BEP[k]->play();

            BZombie[k]->BZ_Movie = new QMovie("BucketheadZombie.gif");
            BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
            BZombie[k]->BZ_Movie->start();
            BZombie[k]->BZ_Label->show();
            BZombie[k]->MS->resume();

        }
    }

    //===================================================

    else if(MyBoxState[CZ_i][k] == 1  && BZombie[k]->HPState == 2)
    {
        if(PS[CZ_i][k]->HP > 0)
        {
            PS[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(PS[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete PS[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            BZombieEat[k]=0;

            BEP[k]->stop();
            delete BEPList[k];
            BEPList[k] = new QMediaPlaylist;
            BEPList[k]->addMedia(QUrl("chomp.mp3"));
            BEP[k]->setPlaylist(CEPList[k]);
            BEP[k]->play();

            BZombie[k]->BZ_Movie = new QMovie("Zombie.gif");
            BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
            BZombie[k]->BZ_Movie->start();
            BZombie[k]->BZ_Label->show();
            BZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 2 && BZombie[k]->HPState == 2)
    {
        if(SF[CZ_i][k]->HP > 0)
        {
            SF[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(SF[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete SF[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            BZombieEat[k]=0;

            BEP[k]->stop();
            delete BEPList[k];
            BEPList[k] = new QMediaPlaylist;
            BEPList[k]->addMedia(QUrl("chomp.mp3"));
            BEP[k]->setPlaylist(BEPList[k]);
            BEP[k]->play();

            BZombie[k]->BZ_Movie = new QMovie("Zombie.gif");
            BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
            BZombie[k]->BZ_Movie->start();
            BZombie[k]->BZ_Label->show();
            BZombie[k]->MS->resume();
        }
    }

    else if(MyBoxState[CZ_i][k] == 3 && BZombie[k]->HPState == 2)
    {
        if(WN[CZ_i][k]->HP > 210)
        {
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <=210 && WN[CZ_i][k]->HP >= 170)
        {
            QMovie * movie= new QMovie("WallNut_cracked1.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 170 && WN[CZ_i][k]->HP > 110)
        {
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 110 && WN[CZ_i][k]->HP >= 70)
        {
            QMovie * movie= new QMovie("WallNut_cracked2.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 70 && WN[CZ_i][k]->HP > 0)
        {
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete WN[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            BZombieEat[k]=0;

            BEP[k]->stop();
            delete BEPList[k];
            BEPList[k] = new QMediaPlaylist;
            BEPList[k]->addMedia(QUrl("chomp.mp3"));
            BEP[k]->setPlaylist(BEPList[k]);
            BEP[k]->play();

            BZombie[k]->BZ_Movie = new QMovie("Zombie.gif");
            BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
            BZombie[k]->BZ_Movie->start();
            BZombie[k]->BZ_Label->show();
            BZombie[k]->MS->resume();

        }
    }

    //============================================================

    else if(MyBoxState[CZ_i][k] == 1  && BZombie[k]->HPState == 1)
    {
        if(PS[CZ_i][k]->HP > 0)
        {
            PS[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(PS[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete PS[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            BZombieEat[k]=0;

            BEP[k]->stop();
            delete BEPList[k];
            BEPList[k] = new QMediaPlaylist;
            BEPList[k]->addMedia(QUrl("chomp.mp3"));
            BEP[k]->setPlaylist(CEPList[k]);
            BEP[k]->play();

            BZombie[k]->BZ_Movie = new QMovie("ZombieLostHead.gif");
            BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
            BZombie[k]->BZ_Movie->start();
            BZombie[k]->BZ_Label->show();
            BZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 2 && BZombie[k]->HPState == 1)
    {
        if(SF[CZ_i][k]->HP > 0)
        {
            SF[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(SF[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete SF[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            BZombieEat[k]=0;

            BEP[k]->stop();
            delete BEPList[k];
            BEPList[k] = new QMediaPlaylist;
            BEPList[k]->addMedia(QUrl("chomp.mp3"));
            BEP[k]->setPlaylist(BEPList[k]);
            BEP[k]->play();

            BZombie[k]->BZ_Movie = new QMovie("ZombieLostHead.gif");
            BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
            BZombie[k]->BZ_Movie->start();
            BZombie[k]->BZ_Label->show();
            BZombie[k]->MS->resume();
        }
    }

    else if(MyBoxState[CZ_i][k] == 3 && BZombie[k]->HPState == 1)
    {
        if(WN[CZ_i][k]->HP > 210)
        {
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <=210 && WN[CZ_i][k]->HP >= 170)
        {
            QMovie * movie= new QMovie("WallNut_cracked1.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 170 && WN[CZ_i][k]->HP > 110)
        {
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 110 && WN[CZ_i][k]->HP >= 70)
        {
            QMovie * movie= new QMovie("WallNut_cracked2.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 70 && WN[CZ_i][k]->HP > 0)
        {
            WN[CZ_i][k]->HP -= BZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete WN[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            BZombieEat[k]=0;

            BEP[k]->stop();
            delete BEPList[k];
            BEPList[k] = new QMediaPlaylist;
            BEPList[k]->addMedia(QUrl("chomp.mp3"));
            BEP[k]->setPlaylist(BEPList[k]);
            BEP[k]->play();

            BZombie[k]->BZ_Movie = new QMovie("ZombieLostHead.gif");
            BZombie[k]->BZ_Label->setMovie(BZombie[k]->BZ_Movie);
            BZombie[k]->BZ_Movie->start();
            BZombie[k]->BZ_Label->show();
            BZombie[k]->MS->resume();

        }
    }
}

void MyGame::PDeleteP(int CZ_i,int k)
{
    if(MyBoxState[CZ_i][k] == 1 && PZombie[k]->HPState == 2)
    {
        if(PS[CZ_i][k]->HP > 0)
        {
            PS[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(PS[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete PS[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            PZombieEat[k]=1;

            PEP[k]->stop();
            delete PEPList[k];
            PEPList[k] = new QMediaPlaylist;
            PEPList[k]->addMedia(QUrl("chomp.mp3"));
            PEP[k]->setPlaylist(PEPList[k]);
            PEP[k]->play();

            PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieWalk.gif");
            PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
            PZombie[k]->PZ_Movie->start();
            PZombie[k]->PZ_Label->show();
            PZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 2 && PZombie[k]->HPState == 2)
    {
        if(SF[CZ_i][k]->HP > 0)
        {
            SF[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(SF[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete SF[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            PZombieEat[k]=1;

            PEP[k]->stop();
            delete PEPList[k];
            PEPList[k] = new QMediaPlaylist;
            PEPList[k]->addMedia(QUrl("chomp.mp3"));
            PEP[k]->setPlaylist(PEPList[k]);
            PEP[k]->play();

            PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieWalk.gif");
            PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
            PZombie[k]->PZ_Movie->start();
            PZombie[k]->PZ_Label->show();
            PZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 3 && PZombie[k]->HPState == 2)
    {
        if(WN[CZ_i][k]->HP > 210)
        {
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <=210 && WN[CZ_i][k]->HP >= 170)
        {
            QMovie * movie= new QMovie("WallNut_cracked1.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 170 && WN[CZ_i][k]->HP > 110)
        {
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 110 && WN[CZ_i][k]->HP >= 70)
        {
            QMovie * movie= new QMovie("WallNut_cracked2.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 70 && WN[CZ_i][k]->HP > 0)
        {
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete WN[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            PZombieEat[k]=1;

            PEP[k]->stop();
            delete PEPList[k];
            PEPList[k] = new QMediaPlaylist;
            PEPList[k]->addMedia(QUrl("chomp.mp3"));
            PEP[k]->setPlaylist(PEPList[k]);
            PEP[k]->play();

            PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieWalk.gif");
            PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
            PZombie[k]->PZ_Movie->start();
            PZombie[k]->PZ_Label->show();
            PZombie[k]->MS->resume();

        }
    }

    //==========================================================

    if(MyBoxState[CZ_i][k] == 1 && PZombie[k]->HPState == 1 && PZombie[k]->PoleState == 1)
    {
        if(PS[CZ_i][k]->HP > 0)
        {
            PS[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(PS[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete PS[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            PZombieEat[k]=1;

            PEP[k]->stop();
            delete PEPList[k];
            PEPList[k] = new QMediaPlaylist;
            PEPList[k]->addMedia(QUrl("chomp.mp3"));
            PEP[k]->setPlaylist(PEPList[k]);
            PEP[k]->play();

            PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieLostHead.gif");
            PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
            PZombie[k]->PZ_Movie->start();
            PZombie[k]->PZ_Label->show();
            PZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 2 && PZombie[k]->HPState == 1 && PZombie[k]->PoleState == 1)
    {
        if(SF[CZ_i][k]->HP > 0)
        {
            SF[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(SF[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete SF[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            PZombieEat[k]=1;

            PEP[k]->stop();
            delete PEPList[k];
            PEPList[k] = new QMediaPlaylist;
            PEPList[k]->addMedia(QUrl("chomp.mp3"));
            PEP[k]->setPlaylist(PEPList[k]);
            PEP[k]->play();

            PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieLostHead.gif");
            PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
            PZombie[k]->PZ_Movie->start();
            PZombie[k]->PZ_Label->show();
            PZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 3 && PZombie[k]->HPState == 1 && PZombie[k]->PoleState == 1)
    {
        if(WN[CZ_i][k]->HP > 210)
        {
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <=210 && WN[CZ_i][k]->HP >= 170)
        {
            QMovie * movie= new QMovie("WallNut_cracked1.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 170 && WN[CZ_i][k]->HP > 110)
        {
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 110 && WN[CZ_i][k]->HP >= 70)
        {
            QMovie * movie= new QMovie("WallNut_cracked2.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 70 && WN[CZ_i][k]->HP > 0)
        {
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete WN[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            PZombieEat[k]=1;

            PEP[k]->stop();
            delete PEPList[k];
            PEPList[k] = new QMediaPlaylist;
            PEPList[k]->addMedia(QUrl("chomp.mp3"));
            PEP[k]->setPlaylist(PEPList[k]);
            PEP[k]->play();

            PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieLostHead.gif");
            PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
            PZombie[k]->PZ_Movie->start();
            PZombie[k]->PZ_Label->show();
            PZombie[k]->MS->resume();

        }
    }

    //===========================================================

    if(MyBoxState[CZ_i][k] == 1 && PZombie[k]->HPState == 1 && PZombie[k]->PoleState == 0)
    {
        if(PS[CZ_i][k]->HP > 0)
        {
            PS[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(PS[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete PS[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            PZombieEat[k]=1;

            PEP[k]->stop();
            delete PEPList[k];
            PEPList[k] = new QMediaPlaylist;
            PEPList[k]->addMedia(QUrl("chomp.mp3"));
            PEP[k]->setPlaylist(PEPList[k]);
            PEP[k]->play();

            PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieLostHeadWalk.gif");
            PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
            PZombie[k]->PZ_Movie->start();
            PZombie[k]->PZ_Label->show();
            PZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 2 && PZombie[k]->HPState == 1 && PZombie[k]->PoleState == 0)
    {
        if(SF[CZ_i][k]->HP > 0)
        {
            SF[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(SF[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete SF[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            PZombieEat[k]=1;

            PEP[k]->stop();
            delete PEPList[k];
            PEPList[k] = new QMediaPlaylist;
            PEPList[k]->addMedia(QUrl("chomp.mp3"));
            PEP[k]->setPlaylist(PEPList[k]);
            PEP[k]->play();

            PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieLostHeadWalk.gif");
            PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
            PZombie[k]->PZ_Movie->start();
            PZombie[k]->PZ_Label->show();
            PZombie[k]->MS->resume();

        }
    }

    else if(MyBoxState[CZ_i][k] == 3 && PZombie[k]->HPState == 1 && PZombie[k]->PoleState == 0)
    {
        if(WN[CZ_i][k]->HP > 210)
        {
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <=210 && WN[CZ_i][k]->HP >= 170)
        {
            QMovie * movie= new QMovie("WallNut_cracked1.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 170 && WN[CZ_i][k]->HP > 110)
        {
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 110 && WN[CZ_i][k]->HP >= 70)
        {
            QMovie * movie= new QMovie("WallNut_cracked2.gif");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP < 70 && WN[CZ_i][k]->HP > 0)
        {
            WN[CZ_i][k]->HP -= PZombie[k]->Power;
        }

        else if(WN[CZ_i][k]->HP <= 0)
        {
            QMovie * movie = new QMovie("");
            MyBox[CZ_i][k]->setMovie(movie);
            movie->start();
            MyBox[CZ_i][k]->show();

                delete WN[CZ_i][k];

            MyBoxState[CZ_i][k] = 0;

            PZombieEat[k]=1;

            PEP[k]->stop();
            delete PEPList[k];
            PEPList[k] = new QMediaPlaylist;
            PEPList[k]->addMedia(QUrl("chomp.mp3"));
            PEP[k]->setPlaylist(PEPList[k]);
            PEP[k]->play();

            PZombie[k]->PZ_Movie = new QMovie("PoleVaultingZombieLostHeadWalk.gif");
            PZombie[k]->PZ_Label->setMovie(PZombie[k]->PZ_Movie);
            PZombie[k]->PZ_Movie->start();
            PZombie[k]->PZ_Label->show();
            PZombie[k]->MS->resume();

        }
    }
}

void MyGame::SSVS()
{
    SetSunValue();
}

void MyGame::SetMyBox()
{
    int i=0;
    int j=0;
    int wid=80;
    int hei=95;

    MyBox = new QLabel**[9];

    for(i=0;i<9;i++)
    {
        MyBox[i] = new QLabel*[5];
        for(j=0;j<5;j++)
        {
            MyBox[i][j] = new QLabel(this);
            MyBoxState[i][j] = 0;
        }
    }

    for(i=0;i<9;i++)
    {
        for(j=0;j<5;j++)
        {
            MyBox[i][j]->move(85 + i*wid , 90 + j*hei);
            MyBox[i][j]->resize(wid,hei);
            //MyBox[i][j]->setPixmap(QPixmap("1.png"));
            //MyBox[i][j]->show();
        }
    }

}

void MyGame::SetSun()
{
    btn1 = new TOOTBtn("Sun.gif",this,SetSunNum);

    connect(btn1,SIGNAL(clicked()),this,SLOT(GetSun()));

    SetSunNum++;
}

void MyGame::GetSun()
{
    SunValueNum += 25;
    SetSunValue();
}

void MyGame::GameStart()
{
    MoveCard();
}

void MyGame::AnimStart()
{
    delete CT;
    QPAT->start(500);

    connect(QPAT,SIGNAL(timeout()),this,SLOT(QPAStart1()));
}

void MyGame::HideThisW()
{
    if(CountN==1)
    {
        BGlabel->hide();
        QPB->close();
        label->hide();
        delete TB1timer;
        delete TB2timer;
    }
}

void MyGame::OnPressBtn()
{
    QPixmap PM2("SelectorScreenStartAdventure_32.png");
    QIcon normalIcon(PM2);
    QPB->setIcon(normalIcon);
}

void MyGame::OnReleaseBtn()
{
    QIcon pressIcon("SelectorScreenStartAdventure_32_1.png");
    QPB->setIcon(pressIcon);
}

void MyGame::TB1()
{
    QPixmap PM("SelectorScreenStartAdventure_32_1.png");
    QIcon normalIcon(PM);
    QPB->setIcon(normalIcon);
    TB1timer->start(200);
    connect(TB1timer,SIGNAL(timeout()),this,SLOT(TB2()));
    connect(TB1timer,SIGNAL(timeout()),TB1timer,SLOT(stop()));
}

void MyGame::TB2()
{
    QPixmap PM1("SelectorScreenStartAdventure_32.png");
    QIcon pressIcon(PM1);
    QPB->setIcon(pressIcon);
    TB2timer->start(200);
    connect(TB2timer,SIGNAL(timeout()),this,SLOT(TB1()));
    connect(TB2timer,SIGNAL(timeout()),TB2timer,SLOT(stop()));
}

void MyGame::TwinkleBtn()
{

    if(TBNum==0)
    {
        TBNum++;
        TB1timer = new QTimer;
        TB2timer = new QTimer;
        TB1();
    }
}

void MyGame::ZH()
{
    HandNum++;
    ZombieHand();
}

void MyGame::ZombieHand()
{
    QTimer * timer = new QTimer;

    if(HandNum==0)
    {
        ZombieHandMusic();
        label = new QLabel(this);
        label->setPixmap(QPixmap("ZombieHand1.png"));
        label->move(230,270);
        label->show();
        timer->start(100);
        connect(timer,SIGNAL(timeout()),this,SLOT(ZH()));
        connect(timer,SIGNAL(timeout()),label,SLOT(hide()));
    }
    else if(HandNum==1)
    {
        label = new QLabel(this);
        label->setPixmap(QPixmap("ZombieHand2.png"));
        label->move(230,270);
        label->show();
        timer->start(100);
        connect(timer,SIGNAL(timeout()),this,SLOT(ZH()));
        connect(timer,SIGNAL(timeout()),label,SLOT(hide()));
    }
    else if(HandNum==2)
    {
        label = new QLabel(this);
        label->setPixmap(QPixmap("ZombieHand3.png"));
        label->move(230,270);
        label->show();
        timer->start(100);
        connect(timer,SIGNAL(timeout()),this,SLOT(ZH()));
        connect(timer,SIGNAL(timeout()),label,SLOT(hide()));
    }
    else if(HandNum==4)
    {
        label = new QLabel(this);
        label->setPixmap(QPixmap("ZombieHand4.png"));
        label->move(230,270);
        label->show();
        timer->start(100);
        connect(timer,SIGNAL(timeout()),this,SLOT(ZH()));
        connect(timer,SIGNAL(timeout()),label,SLOT(hide()));
    }
    else if(HandNum==10)
    {
        label = new QLabel(this);
        label->setPixmap(QPixmap("ZombieHand5.png"));
        label->move(230,270);
        label->show();
        timer->start(100);
        connect(timer,SIGNAL(timeout()),this,SLOT(ZH()));
        connect(timer,SIGNAL(timeout()),label,SLOT(hide()));
    }
    else if(HandNum==11)
    {
        label = new QLabel(this);
        label->setPixmap(QPixmap("ZombieHand6.png"));
        label->move(230,270);
        label->show();
        HandNum++;
        delete timer;
    }
    else
        return;
}

void MyGame::MyStartMusic()
{

    player = new QMediaPlayer;
    DirtR = new QMediaPlayer;
    player->setMedia(QUrl("Faster.mp3"));
    player->play();
}

void MyGame::ZombieHandMusic()
{
    player->stop();
    mediaList = new QMediaPlaylist;
    DirtRList = new QMediaPlaylist;
    mediaList->addMedia(QUrl("losemusic.mp3"));
    DirtRList->addMedia(QUrl("dirt_rise.mp3"));
    player->setPlaylist(mediaList);
    DirtR->setPlaylist(DirtRList);
    mediaList->setCurrentIndex(1);
    DirtRList->setCurrentIndex(1);
    player->play();
    DirtR->play();

    ZHtimer = new QTimer;
    ZHtimer -> start(1200);
    connect(ZHtimer,SIGNAL(timeout()),this,SLOT(ZombieHandMusic2()));

}

void MyGame::ZombieHandMusic2()
{
    if(ZHNum == 0)
    {
        player2 = new QMediaPlayer;
        mediaList2 = new QMediaPlaylist;
        mediaList2->addMedia(QUrl("evillaugh.mp3"));
        player2->setPlaylist(mediaList2);
        mediaList2->setCurrentIndex(1);
        player2->play();
        ZHNum++;
        delete ZHtimer;
    }
}

DragItem1::DragItem1(QWidget *parent):QLabel(parent)
{
    QImage image(63,71,QImage::Format_ARGB32);
    if(image.load("1.png") == false)
        QMessageBox::warning(this,"ERROR","Load image error!");
    setPixmap(QPixmap::fromImage(image));
}

DragItem2::DragItem2(QWidget *parent):QLabel(parent)
{
    QImage image(63,71,QImage::Format_ARGB32);
    if(image.load("2.png") == false)
        QMessageBox::warning(this,"ERROR","Load image error!");
    setPixmap(QPixmap::fromImage(image));
}

DragItem3::DragItem3(QWidget *parent):QLabel(parent)
{
    QImage image(63,71,QImage::Format_ARGB32);
    if(image.load("3.png") == false)
        QMessageBox::warning(this,"ERROR","Load image error!");
    setPixmap(QPixmap::fromImage(image));
}

DragItem4::DragItem4(QWidget *parent):QLabel(parent)
{
    QImage image(63,71,QImage::Format_ARGB32);
    if(image.load("Shovel.png") == false)
        QMessageBox::warning(this,"ERROR","Load image error!");
    setPixmap(QPixmap::fromImage(image));
}

void MyGame::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
    {
        event->ignore();
        return;
    }

    QMediaPlayer * PlantS = new QMediaPlayer;
    QMediaPlaylist * PlantSL = new QMediaPlaylist;
    PlantSL->addMedia(QUrl("plant2.mp3"));
    PlantS->setPlaylist(PlantSL);
    PlantSL->setCurrentIndex(1);

    if(CanCS == TRUE)
    {

        SunValueNum = *PSun;
        SetSunValue();
        //

        if(event->pos().x() <= PCard1->pos().x()  + PCard1->width()
            && event->pos().x() >= PCard1->pos().x()
            && event->pos().y() >= PCard1->pos().y()
            && event->pos().y() <= PCard1->pos().y() + PCard1->height()
                && SunValueNum >=100
                && PeaCDvalue == 0)
        {
            DIT1 = new DragItem1(this);
            DIT1->move(event->pos().x() - 32,event->pos().y() - 35);
            DIT1->show();
            DITNum1=1;

            PlantS->play();
        }
        else
        {
                DIT1 = new DragItem1(this);
        }

        //

        if(event->pos().x() <= PCard2->pos().x()  + PCard2->width()
            && event->pos().x() >= PCard2->pos().x()
            && event->pos().y() >= PCard2->pos().y()
            && event->pos().y() <= PCard2->pos().y() + PCard2->height()
                && SunValueNum >=50
                && SunCDvalue == 0)
        {
            DIT2 = new DragItem2(this);
            DIT2->move(event->pos().x() - 32,event->pos().y() - 35);
            DIT2->show();
            DITNum2=1;

            PlantS->play();
        }
        else
        {
                DIT2 = new DragItem2(this);
        }

        //

        if(event->pos().x() <= PCard3->pos().x()  + PCard3->width()
            && event->pos().x() >= PCard3->pos().x()
            && event->pos().y() >= PCard3->pos().y()
            && event->pos().y() <= PCard3->pos().y() + PCard3->height()
                && SunValueNum >=50
                && WallCDvalue == 0)
        {
            DIT3 = new DragItem3(this);
            DIT3->move(event->pos().x() - 32,event->pos().y() - 35);
            DIT3->show();
            DITNum3=1;

            PlantS->play();
        }
        else
        {
                DIT3 = new DragItem3(this);
        }

        //

        if(event->pos().x() <= Shovel->pos().x()  + Shovel->width()
            && event->pos().x() >= Shovel->pos().x()
            && event->pos().y() >= Shovel->pos().y()
            && event->pos().y() <= Shovel->pos().y() + Shovel->height())
        {
            DIT4 = new DragItem4(this);
            DIT4->move(event->pos().x() - 38,event->pos().y() - 17);
            DIT4->show();
            DITNum4=1;

            PlantS->play();
        }
        else
        {
                DIT4 = new DragItem4(this);
        }
    }
    else
    {
        DIT1 = new DragItem1(this);
        DIT2 = new DragItem2(this);
        DIT3 = new DragItem3(this);
        DIT4 = new DragItem4(this);
    }
}

void MyGame::mouseMoveEvent(QMouseEvent *event)
{

    if(DITNum1==1)
    {
        DIT1->move(event->pos().x() - 32,event->pos().y() - 35);
    }

    else if(DITNum2==1)
    {
        DIT2->move(event->pos().x() - 32,event->pos().y() - 35);
    }

    else if(DITNum3==1)
    {
        DIT3->move(event->pos().x() - 32,event->pos().y() - 35);
    }

    else if(DITNum4==1)
    {
        DIT4->move(event->pos().x() - 38,event->pos().y() - 17);
    }

    update();
}

void MyGame::mouseReleaseEvent(QMouseEvent *event)
{
    int i=0;
    int j=0;

    if(event->button() != Qt::LeftButton)
    {
        event->ignore();
        return;
    }


    QMediaPlayer * PlantS = new QMediaPlayer;
    QMediaPlaylist * PlantSL = new QMediaPlaylist;
    PlantSL->addMedia(QUrl("plant1.mp3"));
    PlantS->setPlaylist(PlantSL);
    PlantSL->setCurrentIndex(1);

    if(CanCS == TRUE)
    {
        SunValueNum = *PSun;
        SetSunValue();

    for(i=0;i<9;i++)
    {
        for(j=0;j<5;j++)
        {
            if(event->pos().x() <= MyBox[i][j]->pos().x()  + MyBox[i][j]->width()
                && event->pos().x() >= MyBox[i][j]->pos().x()
                && event->pos().y() >= MyBox[i][j]->pos().y()
                && event->pos().y() <= MyBox[i][j]->pos().y() + MyBox[i][j]->height())
                {
                    if(DITNum1==1 && MyBoxState[i][j] ==0 && SunValueNum >= 100 && PeaCDvalue == 0)
                    {
                        PS[i][j] = new Peashooter(this);
                        PS[i][j]->Px = MyBox[i][j]->pos().x();
                        PS[i][j]->Py = MyBox[i][j]->pos().y();

                        MyBox[i][j]->setMovie(PS[i][j]->P_Pea);
                        PS[i][j]->P_Pea->start();
                        MyBox[i][j]->show();
                        MyBoxState[i][j] = 1;


                        SunValueNum -= 100;
                        SetSunValue();

                        PlantS->play();

                        PCard1->setPixmap(QPixmap("Peashooter2.png"));
                        CDTimer1 = new QTimer;
                        CDTimer1->start(7350);
                        PeaCDvalue = 1;
                        connect(CDTimer1,SIGNAL(timeout()),this,SLOT(CoolDown1()));
                    }

                    else if(DITNum2==1 && MyBoxState[i][j] ==0 && SunValueNum >= 50 && SunCDvalue == 0)
                    {
                        Px = MyBox[i][j]->pos().x();
                        Py = MyBox[i][j]->pos().y();

                        SF[i][j] = new SunFlower(this , Px , Py , PSun);
                        MyBox[i][j]->setMovie(SF[i][j]->S_Sun);
                        SF[i][j]->S_Sun->start();
                        MyBox[i][j]->show();
                        MyBoxState[i][j] = 2;


                        SunValueNum -= 50;
                        SetSunValue();

                        PlantS->play();


                        PCard2->setPixmap(QPixmap("SunFlower2.png"));
                        CDTimer2 = new QTimer;
                        CDTimer2->start(7350);
                        SunCDvalue = 1;
                        connect(CDTimer2,SIGNAL(timeout()),this,SLOT(CoolDown2()));
                    }

                    else if(DITNum3==1 && MyBoxState[i][j] ==0 && SunValueNum >= 50 && WallCDvalue == 0)
                    {
                        WN[i][j] = new WallNut(this);
                        MyBox[i][j]->setMovie(WN[i][j]->W_Wall);
                        WN[i][j]->W_Wall->start();
                        MyBox[i][j]->show();
                        MyBoxState[i][j] = 3;


                        SunValueNum -= 50;
                        SetSunValue();

                        PlantS->play();

                        PCard3->setPixmap(QPixmap("WallNut2.png"));
                        CDTimer3 = new QTimer;
                        CDTimer3->start(30000);
                        WallCDvalue = 1;
                        connect(CDTimer3,SIGNAL(timeout()),this,SLOT(CoolDown3()));
                    }

                    else if(DITNum4==1)
                    {
                        QMovie * movie = new QMovie("");
                        MyBox[i][j]->setMovie(movie);
                        movie->start();
                        MyBox[i][j]->show();

                        if(MyBoxState[i][j]==1)
                        {
                            delete PS[i][j];
                        }

                        else if(MyBoxState[i][j]==2)
                        {
                            delete SF[i][j];
                        }

                        else if(MyBoxState[i][j]==2)
                        {
                            delete WN[i][j];
                        }


                        MyBoxState[i][j] = 0;


                        PlantS->play();

                    }
                }
            }
        }
    }
    delete DIT1;
    delete DIT2;
    delete DIT3;
    delete DIT4;
    DITNum1=0;
    DITNum2=0;
    DITNum3=0;
    DITNum4=0;
}

void MyGame::SetSunValue()
{
    if(SunValueNum >= 100)
    {
        if(PeaCDvalue == 0)
        {
            PCard1->setPixmap(QPixmap("Peashooter1.png"));
        }
        if(SunCDvalue == 0)
        {
            PCard2->setPixmap(QPixmap("SunFlower1.png"));
        }

        if(WallCDvalue == 0)
        {
            PCard3->setPixmap(QPixmap("WallNut1.png"));
        }
    }

    else if(SunValueNum < 100 && SunValueNum >=50)
    {
        PCard1->setPixmap(QPixmap("Peashooter2.png"));
        if(SunCDvalue == 0)
        {
            PCard2->setPixmap(QPixmap("SunFlower1.png"));
        }

        if(WallCDvalue == 0)
        {
            PCard3->setPixmap(QPixmap("WallNut1.png"));
        }
    }

    else if(SunValueNum < 50)
    {
        PCard1->setPixmap(QPixmap("Peashooter2.png"));
        PCard2->setPixmap(QPixmap("SunFlower2.png"));
        PCard3->setPixmap(QPixmap("WallNut2.png"));
    }
    SunValueNum = *PSun;
    SunString = QString("%1").arg(SunValueNum);
    SunValueLabel->setText(SunString);
}

void MyGame::CoolDown1()
{
    if(SunValueNum>=100)
    {
        PCard1->setPixmap(QPixmap("Peashooter1.png"));
    }
    delete CDTimer1;
    PeaCDvalue = 0;
}

void MyGame::CoolDown2()
{
    if(SunValueNum>=50)
    {
        PCard2->setPixmap(QPixmap("SunFlower1.png"));
    }
    delete CDTimer2;
    SunCDvalue = 0;
}

void MyGame::CoolDown3()
{
    if(SunValueNum>=50)
    {
        PCard3->setPixmap(QPixmap("WallNut1.png"));
    }
    delete CDTimer3;
    WallCDvalue = 0;
}

void MyGame::MyGameStart()
{
    setAcceptDrops (true);
    MyBackground();
}

void MyGame::Victory()
{
    WinMusic = new QMediaPlayer;
    WinMusiclist = new QMediaPlaylist;
    WinMusiclist->addMedia(QUrl("plantsgarden.mp3"));
    WinMusic->setPlaylist(WinMusiclist);
    WinMusiclist->setCurrentIndex(1);
    WinMusic->play();
    GameBGM1->stop();

    QLabel * V = new QLabel(this);
    V->setPixmap(QPixmap("victory.jpg"));
    V->move(85,200);
    V->show();
}

void MyGame::FailSlot()
{
    ZombieNumber = -10;

    QLabel * F = new QLabel(this);
    F->setPixmap(QPixmap("ZombiesWon.png"));
    F->move(200,80);
    F->show();

    QMediaPlayer * S = new QMediaPlayer;
    QMediaPlaylist * SL = new QMediaPlaylist;
    SL->addMedia(QUrl("scream.mp3"));
    S->setPlaylist(SL);
    SL->setCurrentIndex(1);
    S->play();
    GameBGM1->stop();

    QTimer * C = new QTimer;
    C->start(5000);
    connect(C,SIGNAL(timeout()),this,SLOT(close()));
}

dzy::~dzy()
{
    delete ui;
}
