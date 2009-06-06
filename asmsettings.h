// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#ifndef ASMSETTINGS_H
#define ASMSETTINGS_H

#include <QMainWindow>
#include <QSettings>
#include <QDir>
#include <QFileDialog>
#include <QMenu>
#include <QAction>

#include "settingsclass.h"

namespace Ui
{
    class asmSettingsWindow;
}

class asmSettings : public QMainWindow
{
    Q_OBJECT
public:
    asmSettings(settingsClass *s, QWidget *parent);
    ~asmSettings();
private:
    Ui::asmSettingsWindow *ui;
    settingsClass *set;
    QMenu *menu1, *menu2, *menu3;

private slots:
    void on_toolButton_3_released();
    void on_toolButton_5_released();
    void on_toolButton_released();
    void on_pushButton_released();
    void menu1_triggered(QAction *);
    void menu2_triggered(QAction *);
    void menu3_triggered(QAction *);
    void setDefaultSettings();
};

#endif // ASMSETTINGS_H
