// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#ifndef COLORWINDOW_H
#define COLORWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTextCharFormat>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QMap>
#include <QMessageBox>

#include "settingsclass.h"

namespace Ui
{
    class MainWindow;
}

class colorWindow : public QMainWindow
{
    Q_OBJECT
public:
    colorWindow(settingsClass *s, QWidget *parent);
    ~colorWindow();
private:
    Ui::MainWindow *ui;
    settingsClass *sc;
    QMap<QString,QListWidgetItem*> lwil;
    QMap<QString,QTextCharFormat> tcfm;
    QString previous;
    QStringList lst;
    void savePrev();
    void setupFont();
private slots:
    void itemSelect(QString s);
    void updateExample();
    void save();
    void setDefaults();
};

#endif // COLORWINDOW_H
