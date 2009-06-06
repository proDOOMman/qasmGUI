// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#include "codewindow.h"
#include "ui_codewindow.h"

codeWindow::codeWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::codeWindowClass)
{
    codePage = "CP866";
    ui->setupUi(this);
    ui->tabWidget->clear();
    QWidget *back = new QWidget();
    QWidget *pole = new QWidget();
    QHBoxLayout *hbox = new QHBoxLayout(pole);
    listingBrowser = new QTextEdit();
    listingBrowser->setReadOnly(true);
    textEdit = new QTextEdit();
    ln = new LineNumbers(textEdit);
    hbox->addWidget(ln);
    hbox->addWidget(textEdit);
    splitter = new QSplitter(Qt::Vertical,back);
    textBrowser = new QTextEdit();
    textBrowser->setReadOnly(true);
    splitter->addWidget(pole);
    splitter->addWidget(textBrowser);
    //QHBoxLayout *hboxb = new QHBoxLayout(back);
    back->setLayout(new QHBoxLayout());
    back->layout()->addWidget(splitter);
    pushButton = new QPushButton(trUtf8("Компиляция"),this);
    pushButton_2 = new QPushButton(trUtf8("Линковка"),this);
    pushButton_3 = new QPushButton(trUtf8("Запуск"),this);
    pushButton_4 = new QPushButton(trUtf8("Отмена\nоперации"),this);
    pushButton_5 = new QPushButton(trUtf8("Отладчик"),this);
    pushButton_4->setEnabled(false);
    ui->mainToolBar->addWidget(pushButton);
    ui->mainToolBar->addWidget(pushButton_2);
    ui->mainToolBar->addWidget(pushButton_3);
    ui->mainToolBar->addWidget(pushButton_5);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(pushButton_4);
    pushButton->setIcon(this->style()->standardIcon(QStyle::SP_ArrowForward));
    ui->action_tasm->setIcon(pushButton->icon());
    pushButton_2->setIcon(this->style()->standardIcon(QStyle::SP_ArrowDown));
    ui->action_tlink->setIcon(pushButton_2->icon());
    pushButton_3->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
    ui->action_run->setIcon(pushButton_3->icon());
    pushButton_4->setIcon(this->style()->standardIcon(QStyle::SP_BrowserStop));
    ui->action_cansel->setIcon(pushButton_4->icon());
    pushButton_5->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    ui->action_td->setIcon(pushButton_5->icon());
    ui->action->setIcon(this->style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->action_2->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->action_3->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->action_4->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->action_5->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
    ui->action_6->setIcon(this->style()->standardIcon(QStyle::SP_DialogHelpButton));
    ui->action_13->setIcon(this->style()->standardIcon(QStyle::SP_FileIcon));
    ui->action_TASM->setIcon(this->style()->standardIcon(QStyle::SP_TrashIcon));
    set = new settingsClass(this);
    splitter->restoreState(set->getValue("splitter").toByteArray());
    this->restoreState(set->getValue("state").toByteArray());
    this->ui->action_10->setChecked(set->getValue("statusBar").toBool());
    this->ui->action_9->setChecked(ui->mainToolBar->isEnabled());
    curpos = new QLabel("1 : 1",this);
    ui->statusBar->layout()->setAlignment(Qt::AlignRight);
    ui->statusBar->layout()->addWidget(curpos);
    ui->action_9->setChecked(!ui->mainToolBar->isHidden());
    connect(textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(curPosChanged()));
    connect(this->ui->action_5,SIGNAL(triggered()),this,SLOT(colorSet()));
    connect(this->ui->action_TASM,SIGNAL(triggered()),this,SLOT(asmSett()));
    connect(this->ui->action_QT,SIGNAL(triggered()),this,SLOT(aboutQt()));
    connect(this->ui->action_4,SIGNAL(triggered()),this,SLOT(close()));
    connect(this->ui->action,SIGNAL(triggered()),this,SLOT(open()));
    connect(this->ui->action_2,SIGNAL(triggered()),this,SLOT(save()));
    connect(this->ui->action_13,SIGNAL(triggered()),this,SLOT(new_file()));
    connect(this->ui->action_3,SIGNAL(triggered()),this,SLOT(saveAs()));
    connect(this->ui->action_6,SIGNAL(triggered()),this,SLOT(about()));
    connect(this->ui->action_9,SIGNAL(triggered(bool)),ui->mainToolBar,SLOT(setShown(bool)));
    connect(this->ui->action_10,SIGNAL(triggered(bool)),ui->statusBar,SLOT(setShown(bool)));
    connect(pushButton,SIGNAL(released()),this,SLOT(pushButton_released()));
    connect(pushButton_2,SIGNAL(released()),this,SLOT(pushButton_2_released()));
    connect(pushButton_3,SIGNAL(released()),this,SLOT(pushButton_3_released()));
    connect(pushButton_4,SIGNAL(released()),this,SLOT(pushButton_4_released()));
    connect(pushButton_5,SIGNAL(released()),this,SLOT(pushButton_5_released()));
    connect(ui->action_tasm,SIGNAL(triggered()),pushButton,SLOT(click()));
    connect(ui->action_tlink,SIGNAL(triggered()),pushButton_2,SLOT(click()));
    connect(ui->action_run,SIGNAL(triggered()),pushButton_3,SLOT(click()));
    connect(ui->action_cansel,SIGNAL(triggered()),pushButton_4,SLOT(click()));
    connect(ui->action_td,SIGNAL(triggered()),pushButton_5,SLOT(click()));
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(listingLoad(int)));
    foreach(QString s,QTextCodec::availableCodecs())
    {
        QAction *a = new QAction(s,this);
        ui->menu_4->addAction(a);
    }
    connect(ui->menu_4,SIGNAL(triggered(QAction*)),this,SLOT(codingChange(QAction*)));
    h = new highlighter(textEdit->document(), set);
    connect(textEdit->document(), SIGNAL(blockCountChanged(int)),this,SLOT(textChangedSlot()));
    textChanged = false;
    if(QCoreApplication::argc()>1)
    if(!QString(QCoreApplication::arguments().at(1)).isEmpty())
        emit open(QCoreApplication::arguments().at(1));
    if(set->getValue("firstRun").toString()!="no")
    {
        QMessageBox::information(this,trUtf8("Внмание"),
                                 trUtf8("Удачи в изучении Assembler!"));
        set->setValue("firstRun",QVariant(QString("no")));
    }
    ui->tabWidget->addTab(back,trUtf8("Source"));
    ui->tabWidget->addTab(listingBrowser,trUtf8("Listing"));
}

codeWindow::~codeWindow()
{
    delete ui;
}

void codeWindow::new_file()
{
    QMessageBox mb;
    if(textChanged){
        mb.setText(trUtf8("Этот файл был изменен."));
        mb.setInformativeText(trUtf8("Сохранить изменения?"));
        mb.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        mb.setDefaultButton(QMessageBox::Save);
        int ret = mb.exec();
    switch (ret) {
    case QMessageBox::Save:
       emit save();
       break;
    case QMessageBox::Discard:
       qDebug() << "Nothing to do";
       break;
    case QMessageBox::Cancel:
       return;
       break;
    default:
       qDebug() << "O_o";
       break;
       }
    }
    textEdit->clear();
    textBrowser->clear();
    this->setWindowTitle("qasmGUI - New source file");
    fileName.clear();
    tempName.clear();
    lastTempName.clear();
    listingBrowser->clear();
    textChanged = false;
    ui->statusBar->showMessage(trUtf8("Создан новый документ."),2000);
}

void codeWindow::listingLoad(int number)
{
    if(number==0)
        return;
    QFile f;
    if(!fileName.isEmpty())
        f.setFileName(QFileInfo(fileName).absoluteDir().absoluteFilePath(QFileInfo(fileName).completeBaseName().append(".LST")));
    else
    {
        QDir ndir = QDir::temp();
        ndir.cd(tempName);
        f.setFileName(ndir.absoluteFilePath(tempName.append(".LST")));
    }
    if(!f.exists())
    {
        //QMessageBox::information(this,trUtf8("Обидно =("),trUtf8("Файл листинга не был создан."));
        //ui->statusBar->showMessage(trUtf8("Файл листинга не был создан."),2000);
        listingBrowser->setText(trUtf8("Файл листинга не найден"));
        return;
    }
    if(!f.open(QIODevice::Text|QIODevice::ReadOnly))
        return;
    QByteArray ba = f.readAll();
    QTextCodec *tc = QTextCodec::codecForName(codePage);
    listingBrowser->setText(tc->toUnicode(ba));
    ui->statusBar->showMessage(trUtf8("Открыт файл листинга: ").append(f.fileName()),1000);
}

void codeWindow::curPosChanged()
{
    curpos->setText(QString::number(textEdit->textCursor().blockNumber()+1)
                    +" : "+QString::number(textEdit->textCursor().position()-textEdit->textCursor().block().position()+1));
}

void codeWindow::colorSet()
{
    colorWindow *cl = new colorWindow(set, this);
    cl->setWindowModality(Qt::ApplicationModal);
    cl->show();
    connect(cl,SIGNAL(destroyed()),this,SLOT(repaintText()));
}

void codeWindow::repaintText()
{
    qDebug() << "EXPEREMENTAL FEATURE!!! Syntax rehightlighting";
    textEdit->setText(textEdit->toPlainText());
}

void codeWindow::textChangedSlot()
{
        textChanged = true;
}

void codeWindow::about()
{
    QMessageBox::about(this,trUtf8("О программе"),
                       trUtf8("Программа qasmGUI\nАвтор: proDOOMman, 2009\nБета тестер: Иванов Алексей\nFeature requester: Данилов Стас\n\nЛицензия GPLv2 или более поздняя\n\nЛоготип qasmGUI основан на теме XFCE4 Rodent."));
}

void codeWindow::codingChange(QAction *a)
{
    QFont normal;
    normal.setBold(false);
    foreach(QAction *act, ui->menu_4->actions())
        act->setFont(normal);
    normal.setBold(true);
    a->setFont(normal);
    QTextCodec *tc = QTextCodec::codecForName(codePage);
    QByteArray ba = tc->fromUnicode(textEdit->toPlainText());
    if(a->text()==trUtf8("По умолчанию"))
        codePage = "CP866";
    else
        codePage = a->text().toLocal8Bit();
    tc = QTextCodec::codecForName(codePage);
    textEdit->setText(tc->toUnicode(ba));
    ui->statusBar->showMessage(trUtf8("Выбрана кодировка: ").append(codePage),2000);
}

void codeWindow::open(QString fname)
{
    QMessageBox mb;
    if(textChanged){
        mb.setText(trUtf8("Этот файл был изменен."));
        mb.setInformativeText(trUtf8("Сохранить изменения?"));
        mb.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        mb.setDefaultButton(QMessageBox::Save);
        int ret = mb.exec();
    switch (ret) {
    case QMessageBox::Save:
       emit save();
       break;
    case QMessageBox::Discard:
       qDebug() << "Nothing to do";
       break;
    case QMessageBox::Cancel:
       return;
       break;
    default:
       qDebug() << "O_o";
       break;
       }
    }
    fileName = (fname.isEmpty())?
               (QFileDialog::getOpenFileName(this,trUtf8("Открытие файла"),
                                             QDir::currentPath(), trUtf8("Исходники asm (*.ASM *.S);;Все файлы(*.*)"))):(fileName = fname);
    if(fileName.isEmpty())
        return;
    QFile f(fileName);
    f.open(QIODevice::Text|QIODevice::ReadOnly);
    QByteArray ba = f.readAll();
    QTextCodec *tc = QTextCodec::codecForName(codePage);
    textEdit->setText(tc->toUnicode(ba));
    this->setWindowTitle(QString("qasmGUI - %1").arg(fileName));
    textChanged = false;
    ui->statusBar->showMessage(trUtf8("Открыт файл: ").append(fileName),2000);
}

void codeWindow::saveAs(QString s)
{
    if(s.isEmpty())
        fileName = QFileDialog::getSaveFileName(this, trUtf8("Сохранение файла"),
                                                QDir::currentPath(), trUtf8("Исходники asm (*.ASM *.S);;Все файлы(*.*)"));
    else
        fileName = s;
    if(fileName.isEmpty())
        return;
    QFile f(fileName);
    f.open(QIODevice::Text|QIODevice::WriteOnly);
    QTextCodec *tc = QTextCodec::codecForName(codePage);
    QByteArray ba = tc->fromUnicode(textEdit->toPlainText());
    f.write(ba);
    textChanged = false;
    this->setWindowTitle(QString("codeWindow %1").arg(fileName));
    ui->statusBar->showMessage(trUtf8("Сохранен файл: ").append(fileName),2000);
}

void codeWindow::save()
{
    if(fileName.isEmpty()){
        emit saveAs();
        return;
    }
    QFile f(fileName);
    f.open(QIODevice::Text|QIODevice::WriteOnly);
    QTextCodec *tc = QTextCodec::codecForName(codePage);
    QByteArray ba = tc->fromUnicode(textEdit->toPlainText());
    f.write(ba);
    textChanged = false;
    ui->statusBar->showMessage(trUtf8("Сохранен файл: ").append(fileName),2000);
}

void codeWindow::closeEvent(QCloseEvent *ev)
{
    if(!lastTempName.isEmpty())
        rmLastTemp();
    QByteArray state = splitter->saveState();
    set->setValue("splitter",state);
    set->setValue("state",this->saveState());
    set->setValue("statusBar",this->ui->statusBar->isEnabled());
    QMessageBox mb;
    if(textChanged){
    mb.setText(trUtf8("Этот файл был изменен."));
    mb.setInformativeText(trUtf8("Сохранить изменения?"));
    mb.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    mb.setDefaultButton(QMessageBox::Save);
    int ret = mb.exec();
    switch (ret) {
    case QMessageBox::Save:
       emit save();
       ev->accept();
       break;
    case QMessageBox::Discard:
       ev->accept();
       break;
    case QMessageBox::Cancel:
       ev->ignore();
       break;
    default:
       qDebug() << "O_o";
       break;
       }
}
    else
    ev->accept();
}

void codeWindow::aboutQt()
{
    QMessageBox::aboutQt(this, trUtf8("About QT"));
}

void codeWindow::asmSett()
{
    asmSettings *as = new asmSettings(set,this);
    as->setWindowModality(Qt::ApplicationModal);
    as->show();
}

void codeWindow::pushButton_released()
{
    //compile
    tempName = QString::number(qChecksum(textEdit->toPlainText().toLocal8Bit(),textEdit->toPlainText().toLocal8Bit().length()));
    if(tempName!=lastTempName)
        rmLastTemp();
    lastTempName=tempName;
    qDebug() << tempName;
    QDir ndir = QDir::temp();
    ndir.cd(tempName);
    QFile f(ndir.absoluteFilePath(tempName+".ASM"));
    qDebug() << ndir.absoluteFilePath(tempName);
    if(!f.open(QIODevice::Text|QIODevice::WriteOnly))
        return;
    QTextCodec *tc = QTextCodec::codecForName(codePage);
    QByteArray ba = tc->fromUnicode(textEdit->toPlainText());
    f.write(ba);
    f.close();
    p = new QProcess(this);
    p->setWorkingDirectory(ndir.absolutePath());
    QString tasm = "\""+set->getValue("tasm").toString().append("\" ").append(set->getValue("tasmOpts").toString()).append(" ").append(tempName);
    if(!makeBat(tempName+".compile.bat", tasm))
        return;
    p->start(ndir.absoluteFilePath(tempName+".compile.bat"));
    if(!p->waitForStarted(2000))
        return;
    pushButton->setEnabled(false);
    pushButton_2->setEnabled(false);
    pushButton_3->setEnabled(false);
    pushButton_5->setEnabled(false);
    pushButton_4->setEnabled(true);
    ui->action_tasm->setEnabled(false);
    ui->action_tlink->setEnabled(false);
    ui->action_td->setEnabled(false);
    ui->action_run->setEnabled(false);
    ui->action_cansel->setEnabled(true);
    textBrowser->clear();
    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(readyRead()));
    connect(p, SIGNAL(finished(int)), this, SLOT(procFinish(int)));
    ui->statusBar->showMessage(trUtf8("Компиляция программы..."),2000);
}

void codeWindow::rmLastTemp()
{
    QDir dir = QDir::temp();
    dir.mkdir(tempName);
    //удаляем предыдущие файлы
    if(lastTempName.isEmpty())
        return;
    if(!dir.cd(lastTempName))
        return;
    foreach(QString fname, dir.entryList())
        dir.remove(fname);
    dir.cdUp();
    dir.rmdir(lastTempName);
}

void codeWindow::procFinish(int exitCode)
{
    pushButton->setEnabled(true);
    pushButton_2->setEnabled(true);
    pushButton_3->setEnabled(true);
    pushButton_5->setEnabled(true);
    pushButton_4->setEnabled(false);
    ui->action_tasm->setEnabled(true);
    ui->action_tlink->setEnabled(true);
    ui->action_td->setEnabled(true);
    ui->action_run->setEnabled(true);
    ui->action_cansel->setEnabled(false);
    if(exitCode!=0)
        textBrowser->append(trUtf8("Обнаружена ошибка!"));
    else
    {
        textBrowser->append(trUtf8("Операция завершилась успешно."));
        emit listingLoad(666);
        if(fileName.isEmpty())
            return;
        QDir tdir = QDir::temp();
        tdir.cd(tempName);
        foreach(QString fn, tdir.entryList(QDir::Files))
        {
            if((QFileInfo(tdir.absoluteFilePath(fn)).suffix()!="ASM")&&(QFileInfo(tdir.absoluteFilePath(fn)).suffix()!="bat"))
            {
            QFile::remove(QFileInfo(fileName).absoluteDir().absoluteFilePath(QFileInfo(fileName).completeBaseName().append("."+QFileInfo(tdir,fn).suffix())));
            QFile::copy(tdir.absoluteFilePath(fn), QFileInfo(fileName).absoluteDir().absoluteFilePath(QFileInfo(fileName).completeBaseName().append("."+QFileInfo(tdir,fn).suffix())));
            }
        }
    }
}

void codeWindow::readyRead()
{
    QString s = QTextCodec::codecForName("CP866")->toUnicode(p->readAllStandardOutput());
    s.remove(s.length()-1,1);
    textBrowser->append(s);
}

void codeWindow::pushButton_2_released()
{
    tempName = QString::number(qChecksum(textEdit->toPlainText().toLocal8Bit(),textEdit->toPlainText().toLocal8Bit().length()));
    if(tempName!=lastTempName)
    {
        QMessageBox::information(this,trUtf8("Внимание"),trUtf8("Программа изменилась с момента предыдущей компиляции. Скомпилируйте её повторно."));
        return;
    }
    //link
    rmExe();
    p = new QProcess(this);
    QDir ndir = QDir::temp();
    ndir.cd(tempName);
    p->setWorkingDirectory(ndir.absolutePath());
    QString objName;
    QStringList filters;
    filters << "*.OBJ" << "*.obj";
    ndir.setNameFilters(filters);
    foreach(QString fn, ndir.entryList())
        objName = fn;
    if(objName.isEmpty())
    {
        ui->statusBar->showMessage(trUtf8("Объектный файл не найден, скомпилируйте программу повторно"),2000);
        return;
    }
    QString tlink = "\""+set->getValue("tlink").toString().append("\" ").append(set->getValue("tlinkOpts").toString()).append(" ").append(tempName);
    if(!makeBat(objName+".link.bat",tlink))
        return;
    p->start(ndir.absoluteFilePath(objName+".link.bat"));
    if(!p->waitForStarted(2000))
        return;
    pushButton->setEnabled(false);
    pushButton_2->setEnabled(false);
    pushButton_3->setEnabled(false);
    pushButton_4->setEnabled(true);
    pushButton_5->setEnabled(false);
    ui->action_tasm->setEnabled(false);
    ui->action_tlink->setEnabled(false);
    ui->action_td->setEnabled(false);
    ui->action_run->setEnabled(false);
    ui->action_cansel->setEnabled(true);
    textBrowser->clear();
    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(readyRead()));
    connect(p, SIGNAL(finished(int)), this, SLOT(procFinish(int)));
    ui->statusBar->showMessage(trUtf8("Линковка"),2000);
}

void codeWindow::rmExe()
{
    QDir dir = QDir::tempPath();
    dir.cd(tempName);
    QStringList filters;
    filters << "*.EXE" << "*.exe" << "*.COM" << "*.com";
    dir.setNameFilters(filters);
    foreach(QString fn, dir.entryList())
        dir.remove(fn);
}

bool codeWindow::makeBat(QString file, QString text)
{
    QDir dir = QDir::temp();
    QTextCodec *tc = QTextCodec::codecForName(codePage);
    QByteArray ba = tc->fromUnicode(text);
    dir.cd(tempName);
    QFile f(dir.absoluteFilePath(file));
    if(!f.open(QIODevice::Text|QIODevice::WriteOnly))
        return false;
    f.write(ba);
    f.close();
    return true;
}

void codeWindow::pushButton_4_released()
{
    p->close();
}

void codeWindow::pushButton_5_released()
{
    //debug
    tempName = QString::number(qChecksum(textEdit->toPlainText().toLocal8Bit(),textEdit->toPlainText().toLocal8Bit().length()));
    if(tempName!=lastTempName)
    {
        QMessageBox::information(this,trUtf8("Внимание"),trUtf8("Программа изменилась с момента предыдущей линковки. Слинкуйте её повторно."));
        return;
    }
    textBrowser->clear();
    p = new QProcess(this);
    QString objName;
    QDir ndir = QDir::temp();
    ndir.cd(tempName);
    p->setWorkingDirectory(ndir.absolutePath());
    QStringList filters;
    filters << "*.EXE" << "*.exe" << "*.COM" << "*.com";
    ndir.setNameFilters(filters);
    foreach(QString fn, ndir.entryList())
        objName = fn;
    if(objName.isEmpty())
    {
        ui->statusBar->showMessage(trUtf8("Исполнительный файл не найден, слинкуйте программу повторно"),2000);
        return;
    }
    QString s;
    s = "\""+set->getValue("td").toString().append("\" ").append(set->getValue("tdOpts").toString()).append(" ").append(objName);
    if(!makeBat(objName+".debug.bat",s))
        return;
    p->startDetached(ndir.absoluteFilePath(objName+".debug.bat"),QStringList(),ndir.absolutePath());
    ui->statusBar->showMessage(trUtf8("Запускаем отладчик."),2000);
    if(!p->waitForStarted(2000))
        return;
    pushButton->setEnabled(false);
    pushButton_2->setEnabled(false);
    pushButton_3->setEnabled(false);
    pushButton_4->setEnabled(true);
    pushButton_5->setEnabled(false);
    ui->action_tasm->setEnabled(false);
    ui->action_tlink->setEnabled(false);
    ui->action_td->setEnabled(false);
    ui->action_run->setEnabled(false);
    ui->action_cansel->setEnabled(true);
    connect(p, SIGNAL(finished(int)), this, SLOT(procFinish(int)));
}

void codeWindow::pushButton_3_released()
{
    //start
    tempName = QString::number(qChecksum(textEdit->toPlainText().toLocal8Bit(),textEdit->toPlainText().toLocal8Bit().length()));
    if(tempName!=lastTempName)
    {
        QMessageBox::information(this,trUtf8("Внимание"),trUtf8("Программа изменилась с момента предыдущей линковки. Слинкуйте её повторно."));
        return;
    }
    textBrowser->clear();
    p = new QProcess(this);
    QString objName;
    QDir dir = QDir::temp();
    dir.cd(tempName);
    p->setWorkingDirectory(dir.absolutePath());
    QStringList filters;
    filters << "*.EXE" << "*.exe" << "*.COM" << "*.com";
    dir.setNameFilters(filters);
    foreach(QString fn, dir.entryList())
        objName = fn;
    if(objName.isEmpty())
    {
        ui->statusBar->showMessage(trUtf8("Исполнительный файл не найден, слинкуйте программу повторно"),2000);
        return;
    }
    p->startDetached(dir.absoluteFilePath(objName));
    ui->statusBar->showMessage(trUtf8("Запускаем программу: ")+objName,2000);
    if(!p->waitForStarted(2000))
        return;
    pushButton->setEnabled(false);
    pushButton_2->setEnabled(false);
    pushButton_3->setEnabled(false);
    pushButton_4->setEnabled(true);
    pushButton_5->setEnabled(true);
    ui->action_tasm->setEnabled(false);
    ui->action_tlink->setEnabled(false);
    ui->action_td->setEnabled(false);
    ui->action_run->setEnabled(false);
    ui->action_cansel->setEnabled(true);
    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(readyRead()));
    connect(p, SIGNAL(finished(int)), this, SLOT(procFinish(int)));
}
