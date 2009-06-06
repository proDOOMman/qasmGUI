// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#include "colorwindow.h"
#include "ui_colorwindow.h"

colorWindow::colorWindow(settingsClass *s, QWidget *parent)
    :QMainWindow(parent), ui(new Ui::MainWindow)
{
    sc = s;
    ui->setupUi(this);
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
    foreach(QString name, lst)
        tcfm[name] = sc->getFontFormat(name);
    previous = "identifer";
    setupFont();
    connect(ui->listWidget,SIGNAL(currentTextChanged(QString)),this,SLOT(itemSelect(QString)));
    connect(ui->checkBox,SIGNAL(released()),this,SLOT(updateExample()));
    connect(ui->checkBox_2,SIGNAL(released()),this,SLOT(updateExample()));
    connect(ui->fontComboBox,SIGNAL(currentFontChanged(QFont)),this,SLOT(updateExample()));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(updateExample()));
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(updateExample()));
    connect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),this,SLOT(updateExample()));
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(save()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(setDefaults()));
}

colorWindow::~colorWindow()
{
    delete ui;
}

void colorWindow::save()
{
    savePrev();
    foreach(QString name, lst)
        sc->setFontFormat(name,tcfm[name]);
    QMessageBox::information(this,trUtf8("Внимание"),trUtf8("Подсветка обновляется по мере изменения (набора) текста"));
    this->close();
}

void colorWindow::itemSelect(QString s)
{
    savePrev();
    previous = s;
    setupFont();
}

void colorWindow::updateExample()
{
    QTextCharFormat temp;
    temp.setFont(ui->fontComboBox->currentFont());
    temp.setFontWeight((ui->checkBox->isChecked())?QFont::Bold:QFont::Normal);
    temp.setFontItalic(ui->checkBox_2->isChecked());
    temp.setForeground(QBrush(QColor(ui->horizontalSlider->value(),
                                               ui->horizontalSlider_2->value(),ui->horizontalSlider_3->value())));
    ui->textEdit->setCurrentCharFormat(temp);
    ui->textEdit->setText("Example");
}

void colorWindow::savePrev()
{
    tcfm[previous].setFont(ui->fontComboBox->currentFont());
    tcfm[previous].setFontWeight((ui->checkBox->isChecked())?QFont::Bold:QFont::Normal);
    tcfm[previous].setFontItalic(ui->checkBox_2->isChecked());
    tcfm[previous].setForeground(QBrush(QColor(ui->horizontalSlider->value(),
                                               ui->horizontalSlider_2->value(),ui->horizontalSlider_3->value())));
}

void colorWindow::setupFont()
{
    ui->fontComboBox->setCurrentFont(tcfm[previous].font().family());
    ui->checkBox->setChecked((tcfm[previous].fontWeight()==QFont::Bold)?true:false);
    ui->checkBox_2->setChecked(tcfm[previous].fontItalic());
    ui->horizontalSlider->setValue(tcfm[previous].foreground().color().red());
    ui->horizontalSlider_2->setValue(tcfm[previous].foreground().color().green());
    ui->horizontalSlider_3->setValue(tcfm[previous].foreground().color().blue());
    emit updateExample();
}

void colorWindow::setDefaults()
{
    sc->setDefFonts();
    setupFont();
}
