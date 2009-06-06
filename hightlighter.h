// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#ifndef HIGHTLIGHTER_H
#define HIGHTLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QRegExp>
#include <QMap>
#include <QTextCharFormat>
#include <QList>
#include <QSettings>

#include "settingsclass.h"

class QTextDocument;
class highlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    highlighter(QTextDocument *parent, settingsClass *sc);
protected:
    void highlightBlock(const QString &text);
private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QMap<QString,QStringList> container;
    QMap<QString,QTextCharFormat> containerFormat;
    QVector<HighlightingRule> highlightingRules;
    settingsClass *set;
    QVector<QString> hl;
    void initRules();
};

#endif // HIGHTLIGHTER_H
