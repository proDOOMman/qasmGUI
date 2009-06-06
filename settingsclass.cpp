// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#include "settingsclass.h"

settingsClass::settingsClass(QObject *parent):QObject(parent)
{
    set = new QSettings("KurskLUG","qasmGUI",this);
    changed = false;
    QDir dir = QCoreApplication::applicationDirPath();
    dir.cd("TASM");
    dir.cd("BIN");
    defValue["tasm"] = dir.absoluteFilePath("tasm.exe");
    defValue["tasmOpts"] = "/z /zi /l";
    defValue["tlink"] = dir.absoluteFilePath("tlink.exe");
    defValue["tlinkOpts"] = "/v";
    defValue["td"] = dir.absoluteFilePath("td.exe");
    defValue["tdOpts"] = "";
    defValue["statusBar"] = "true";
    QTextCharFormat def;
    //def = QTextCharFormat:: //TODO: системный шрифт
    defCharFormat["identifer"].setForeground(Qt::blue);
    defCharFormat["number"].setForeground(Qt::red);
    defCharFormat["masmOption"].setFontWeight(QFont::Bold);
    defCharFormat["masmOption"].setForeground(Qt::gray);
    defCharFormat["masmType"].setFontWeight(QFont::Bold);
    defCharFormat["masmType"].setForeground(Qt::magenta);
    defCharFormat["masmOperator"].setFontWeight(QFont::Bold);
    defCharFormat["masmOperator"].setForeground(Qt::darkGreen);
    defCharFormat["masmDirective"].setForeground(Qt::darkCyan);
    defCharFormat["masmRegister"].setForeground(Qt::darkRed);
    defCharFormat["masmOpcode"].setForeground(Qt::darkBlue);
    defCharFormat["masmOpFloat"].setFontWeight(QFont::Bold);
    defCharFormat["masmOpFloat"].setForeground(Qt::darkBlue);
    defCharFormat["proc"].setFontWeight(QFont::Bold);
    defCharFormat["proc"].setFontItalic(true);
    defCharFormat["string"].setFontWeight(QFont::Bold);
    defCharFormat["string"].setForeground(Qt::green);
    defCharFormat["comment"].setFontItalic(true);
    defCharFormat["comment"].setForeground(Qt::darkRed);
}

settingsClass::~settingsClass()
{
    delete set;
}

QVariant settingsClass::getValue(QString s, QString group)
{
    if(group.isEmpty())
        return set->value(s,(defValue.contains(s))?defValue[s]:QVariant());
    set->beginGroup(group);
    QVariant result = set->value(s);
    set->endGroup();
    return result;
}

void settingsClass::setValue(QString s, QVariant v, QString group)
{
    if(group.isEmpty())
    {
        set->setValue(s,v);
        return;
    }
    set->beginGroup(group);
    set->setValue(s,v);
    set->endGroup();
}

void settingsClass::setFontFormat(QString name, QTextCharFormat tcf)
{
    set->beginGroup(name);
    set->setValue("family",tcf.fontFamily());
    set->setValue("bold",(tcf.fontWeight()==QFont::Bold)?true:false);
    set->setValue("italic",tcf.fontItalic());
    set->setValue("r",tcf.foreground().color().red());
    set->setValue("g",tcf.foreground().color().green());
    set->setValue("b",tcf.foreground().color().blue());
    set->endGroup();
    changed = true;
}

void settingsClass::setDefTasm()
{
    set->remove("tasm");
    set->remove("tasmOpts");
    set->remove("tlink");
    set->remove("tlinkOpts");
    set->remove("td");
    set->remove("tdOpts");
}

void settingsClass::setDefFonts()
{
    QStringList lst;
    lst << "identifer"
        << "number"
        << "masmOption"
        << "masmType"
        << "masmOperator"
        << "masmDirective"
        << "masmRegister"
        << "masmOpcode"
        << "masmOpFloat"
        << "proc"
        << "string"
        << "comment";
    foreach(QString rm,lst)
    {
        set->beginGroup(rm);
        set->remove("");
        set->endGroup();
    }
}

QTextCharFormat settingsClass::getFontFormat(QString name)
{
    QTextCharFormat temp;
    set->beginGroup(name);
    temp.setFontFamily(set->value("family",defCharFormat[name].fontFamily()).toString());
    temp.setFontWeight((set->value("bold",(defCharFormat[name].fontWeight()==QFont::Bold)?true:false).toBool())?QFont::Bold:QFont::Normal);
    temp.setFontItalic(set->value("italic",defCharFormat[name].fontItalic()).toBool());
    int r,g,b;
    r = set->value("r",defCharFormat[name].foreground().color().red()).toInt();
    g = set->value("g",defCharFormat[name].foreground().color().green()).toInt();
    b = set->value("b",defCharFormat[name].foreground().color().blue()).toInt();
    temp.setForeground(QBrush(QColor(r,g,b)));
    set->endGroup();
    return temp;
}

bool settingsClass::isChanged()
{
    if(!changed)
        return false;
    changed = false;
    return true;
}
