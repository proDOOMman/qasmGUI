// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#include "asmsettings.h"
#include "ui_asmSetting.h"

asmSettings::asmSettings(settingsClass *s, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::asmSettingsWindow)
{
    set = s;
    ui->setupUi(this);
    ui->lineEdit->setText(set->getValue("tasm").toString());
    ui->lineEdit_2->setText(set->getValue("tasmOpts").toString());
    ui->lineEdit_3->setText(set->getValue("tlink").toString());
    ui->lineEdit_4->setText(set->getValue("tlinkOpts").toString());
    ui->lineEdit_5->setText(set->getValue("td").toString());
    ui->lineEdit_6->setText(set->getValue("tdOpts").toString());
    menu1 = new QMenu(trUtf8("Опции компилятора"),this);
    QStringList sl1;
    sl1 <<  "/a - Alphabetic segment ordering" <<
            "/s - Source-code segment ordering" <<
            "/c - Generate cross-reference in listing" <<
            "/dSYM[=VAL] - Define symbol SYM = 0, or = value VAL" <<
            "/e - Emulated floating-point instructions" <<
            "/r - Real floating-point instructions" <<
            "/iPATH - Search PATH for include files" <<
            "/jCMD - Jam in an assembler directive CMD (eg. /jIDEAL)" <<
            "/kh# - Hash table capacity # symbols" <<
            "/l - Generate listing: l=normal listing" <<
            "/la - Generate listing: la=expanded listing" <<
            "/ml - Case sensitivity on symbols: ml=all" <<
            "/mx - Case sensitivity on symbols: mx=globals" <<
            "/mu - Case sensitivity on symbols: mu=none" <<
            "/mv# - Set maximum valid length for symbols" <<
            "/m# - Allow # multiple passes to resolve forward references" <<
            "/n - Suppress symbol tables in listing" <<
            "/os - Object code: standard" <<
            "/o - Object code: standard w/overlays" <<
            "/op - Object code: Phar Lap" <<
            "/oi - Object code: IBM" <<
            "/p - Check for code segment overrides in protected mode" <<
            "/q - Suppress OBJ records not needed for linking" <<
            "/t - Suppress messages if successful assembly" <<
            "/uxxxx - Set version emulation, version xxxx" <<
            "/w0 - Set warning level: w0=none" <<
            "/w1 - Set warning level: w1=warnings on" <<
            "/w2 - Set warning level: w2=warnings on" <<
            "/w-xxx - Disable (-) warning xxx" <<
            "/w+xxx - Enable (+) warning xxx" <<
            "/x - Include false conditionals in listing" <<
            "/z - Display source line with error message" <<
            "/zi - Debug info: zi=full" <<
            "/zd - Debug info: zd=line numbers only" <<
            "/zn - Debug info: zn=none";
    foreach(QString s, sl1){
        menu1->addAction(s);
    }
    ui->toolButton_2->setMenu(menu1);
    menu2 = new QMenu(trUtf8("Опции линковщика"),this);
    QStringList sl2;
    sl2 <<
        "/x - No map" <<
        "/c - Case sensitive symbols" <<
        "/m - Map including public names" <<
        "/C - Case sensitive exports & imports" <<
        "/M - Map with mangled public names" <<
        "/ye - Expanded memory swapping" <<
        "/s - Map plus detailed segment map" <<
        "/yx - Extended memory swapping" <<
        "/l - Map plus source line #s" <<
        "/d - Warn if duplicate symbols in libraries" <<
        "/i - Initialize all segments" <<
        "/f - Inhibit optimizing far calls to near" <<
        "/L - Specify library search paths" <<
        "/Gx - Goodies n=discard Nonresident name table r=transfer Resident names to nonresident names table" <<
        "/n - Ignore default librariestable" <<
        "/v - Full symbolic debug information" <<
        "/Tti - Specify target & image type. t can be d = DOS (default), w = Windows, x = DPMI, i can be e=EXE or d=DLL" <<
        "/A=dd - Set segment alignment" <<
        "/R[mpekv] - Specify option to RLINK" <<
        "/t - Create COM file (same as /Tdc)" <<
        "/k - Suppress \"No stack\" warning msg" <<
        "/3 - Enable 32-bit processing" <<
        "/Ox - Optimizations: c=chained fixups, i=iterated data, a=minimum segment alignment, r=minimum resource alignment" <<
        "/o - Overlay switch" <<
        "/P[=dd] - Pack code segments" <<
        "/Vd.d - Expected Windows version" <<
        "/j - Specify object search paths";
    foreach(QString s, sl2){
        menu2->addAction(s);
    }
    ui->toolButton_4->setMenu(menu2);
    menu3 = new QMenu(trUtf8("Опции отладчика"),this);
    QStringList sl3;
    sl3
    << "-x- - turn option x off"
    << "-c<file> - Use configuration file <file>"
    << "-do - Screen updating: do=Other display"
    << "-dp - Screen updating: dp=Page flip"
    << "-ds - Screen updating: ds=Screen swap"
    << "-i - Keep user interrupt vectors installed while debugging"
    << "-ji - State restore: i=Ignore old"
    << "-jn - State restore: n=None"
    << "-jp - State restore: p=Prompt old"
    << "-ju - State restore: u=Use old"
    << "-k - Allow keystroke recording"
    << "-l - Assembler startup"
    << "-p - Use mouse"
    << "-r - Use remote debugging"
    << "-ra<#> - Remote network LAN adapter number, default=0"
    << "-rn<L;R> - Debug on a network with local machine L and remote machine R"
    << "-rp<#> - Set COM # port for remote link"
    << "-rs<#> - Remote link speed: 1=slowest, 2=slow, 3=medium, 4=fast"
    << "-sc - No case checking on symbols"
    << "-sd<dir> - Source file directory <dir>"
    << "-vd<dllname> - Use DLL <dllname> for video mode switching"
    << "-vg - Complete graphics screen save"
    << "-vn - 43/50 line display not allowed"
    << "-vp - Enable EGA/VGA palette save";
    foreach(QString s, sl3){
        menu3->addAction(s);
    }
    ui->toolButton_6->setMenu(menu3);
    connect(menu1,SIGNAL(triggered(QAction*)),this,SLOT(menu1_triggered(QAction*)));
    connect(menu2,SIGNAL(triggered(QAction*)),this,SLOT(menu2_triggered(QAction*)));
    connect(menu3,SIGNAL(triggered(QAction*)),this,SLOT(menu3_triggered(QAction*)));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(setDefaultSettings()));
}

asmSettings::~asmSettings()
{
    delete ui;
}

void asmSettings::menu1_triggered(QAction *a)
{
    ui->lineEdit_2->setText(ui->lineEdit_2->text()+' '+a->text().remove(a->text().indexOf(QRegExp(" - ")),a->text().length()-a->text().indexOf(QRegExp(" - "))));
}

void asmSettings::menu2_triggered(QAction *a)
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+' '+a->text().remove(a->text().indexOf(QRegExp(" - ")),a->text().length()-a->text().indexOf(QRegExp(" - "))));
}

void asmSettings::menu3_triggered(QAction *a)
{
    ui->lineEdit_6->setText(ui->lineEdit_6->text()+' '+a->text().remove(a->text().indexOf(QRegExp(" - ")),a->text().length()-a->text().indexOf(QRegExp(" - "))));
}

void asmSettings::on_pushButton_released()
{
    set->setValue("tasm",ui->lineEdit->text());
    set->setValue("tasmOpts",ui->lineEdit_2->text());
    set->setValue("tlink",ui->lineEdit_3->text());
    set->setValue("tlinkOpts",ui->lineEdit_4->text());
    set->setValue("td",ui->lineEdit_5->text());
    set->setValue("tdOpts",ui->lineEdit_6->text());
    this->close();
}

void asmSettings::on_toolButton_released()
{
    QString fname = QFileDialog::getOpenFileName(this,trUtf8("Укажите расположение файла tasm.exe"),
                                                 QDir::currentPath(), trUtf8("Компилятор (tasm.exe);;Все файлы (*.*)"));
    if(fname.isEmpty())
        return;
    ui->lineEdit->setText(fname);
}

void asmSettings::on_toolButton_3_released()
{
    QString fname = QFileDialog::getOpenFileName(this,trUtf8("Укажите расположение файла tlink.exe"),
                                                 QDir::currentPath(), trUtf8("Линковщик (tlink.exe);;Все файлы (*.*)"));
    if(fname.isEmpty())
        return;
    ui->lineEdit_3->setText(fname);
}

void asmSettings::on_toolButton_5_released()
{
    QString fname = QFileDialog::getOpenFileName(this,trUtf8("Укажите расположение файла td.exe"),
                                                 QDir::currentPath(), trUtf8("Отладчик (td.exe);;Все файлы (*.*)"));
    if(fname.isEmpty())
        return;
    ui->lineEdit_5->setText(fname);
}

void asmSettings::setDefaultSettings()
{
    set->setDefTasm();
    ui->lineEdit->setText(set->getValue("tasm").toString());
    ui->lineEdit_2->setText(set->getValue("tasmOpts").toString());
    ui->lineEdit_3->setText(set->getValue("tlink").toString());
    ui->lineEdit_4->setText(set->getValue("tlinkOpts").toString());
    ui->lineEdit_5->setText(set->getValue("td").toString());
    ui->lineEdit_6->setText(set->getValue("tdOpts").toString());
}
