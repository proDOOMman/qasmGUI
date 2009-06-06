// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#ifndef CODEWINDOW_H
#define CODEWINDOW_H

#include <QtGui/QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTextCodec>
#include <QAction>
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QTimer>
#include <QStyle>
#include <QLabel>
#include <QSpacerItem>
#include <QStringList>
#include <QString>

#include "asmsettings.h"
#include "hightlighter.h"
#include "linenumbers.h"
#include "colorwindow.h"
#include "settingsclass.h"

namespace Ui
{
    class codeWindowClass;
}

class codeWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *);

public:
    codeWindow(QWidget *parent = 0);
    ~codeWindow();
    QString tasm, tlink, tasmOpt, tlinkOpt;

private:
    Ui::codeWindowClass *ui;
    QString fileName, tempName, lastTempName;
    QProcess *p;
    QByteArray codePage;
    QTextEdit *textEdit, *textBrowser, *listingBrowser;
    QPushButton *pushButton, *pushButton_2, *pushButton_3, *pushButton_4, *pushButton_5;
    QLabel *curpos;
    QSplitter *splitter;
    QSpacerItem *spi;
    bool textChanged;
    settingsClass *set;
    highlighter *h;
    LineNumbers *ln;
    void rmExe();
    bool makeBat(QString file, QString text);
    void rmLastTemp();

private slots:
    void pushButton_released();
    void pushButton_2_released();
    void pushButton_3_released();
    void pushButton_4_released();
    void pushButton_5_released();
    void readyRead();
    void procFinish(int);
    void asmSett();
    void aboutQt();
    void open(QString fname = 0);
    void save();
    void new_file();
    void about();
    void saveAs(QString s = 0);
    void codingChange(QAction*);
    void textChangedSlot();
    void colorSet();
    void curPosChanged();
    void repaintText();
    void listingLoad(int);
};

#endif // CODEWINDOW_H
