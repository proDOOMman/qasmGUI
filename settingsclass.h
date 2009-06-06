// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H

#include <QObject>
#include <QSettings>
#include <QMap>
#include <QTextCharFormat>
#include <QCoreApplication>
#include <QDir>

class settingsClass : public QObject
{
    Q_OBJECT
public:
    settingsClass(QObject *parent = 0);
    ~settingsClass();
    QVariant getValue(QString s, QString group = 0);
    void setValue(QString s, QVariant v, QString group = 0);
    void setFontFormat(QString name, QTextCharFormat tcf);
    QTextCharFormat getFontFormat(QString name);
    bool isChanged();
    void setDefTasm();
    void setDefFonts();
private:
    QSettings *set;
    bool changed;
    QMap<QString,QVariant> defValue;
    QMap<QString,QTextCharFormat> defCharFormat;
};

#endif // SETTINGSCLASS_H
