/********************************************************************************
** Form generated from reading ui file 'MainWindow.ui'
**
** Created: Mon Aug 6 13:02:32 2007
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *supporter;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    QSize size(647, 492);
    size = size.expandedTo(MainWindow->minimumSizeHint());
    MainWindow->resize(size);
    MainWindow->setWindowIcon(QIcon(QString::fromUtf8("smallIcon.png")));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    supporter = new QFrame(centralwidget);
    supporter->setObjectName(QString::fromUtf8("supporter"));
    supporter->setGeometry(QRect(210, 200, 120, 80));
    supporter->setFrameShape(QFrame::StyledPanel);
    supporter->setFrameShadow(QFrame::Raised);
    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Get Sudoku - The free portable interactive sudoku solver", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // UI_MAINWINDOW_H
