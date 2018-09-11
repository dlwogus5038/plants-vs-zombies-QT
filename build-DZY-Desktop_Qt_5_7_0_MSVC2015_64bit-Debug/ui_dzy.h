/********************************************************************************
** Form generated from reading UI file 'dzy.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DZY_H
#define UI_DZY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dzy
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *dzy)
    {
        if (dzy->objectName().isEmpty())
            dzy->setObjectName(QStringLiteral("dzy"));
        dzy->resize(400, 300);
        centralWidget = new QWidget(dzy);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dzy->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(dzy);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 18));
        dzy->setMenuBar(menuBar);
        mainToolBar = new QToolBar(dzy);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        dzy->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(dzy);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        dzy->setStatusBar(statusBar);

        retranslateUi(dzy);

        QMetaObject::connectSlotsByName(dzy);
    } // setupUi

    void retranslateUi(QMainWindow *dzy)
    {
        dzy->setWindowTitle(QApplication::translate("dzy", "dzy", 0));
    } // retranslateUi

};

namespace Ui {
    class dzy: public Ui_dzy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DZY_H
