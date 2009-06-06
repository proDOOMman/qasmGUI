// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#ifndef LINENUMBERS_H
#define LINENUMBERS_H

#include <QWidget>
#include <QTextCursor>
#include <QTextEdit>
#include <QGridLayout>
#include <QScrollBar>
#include <QPainter>
#include <QAbstractTextDocumentLayout>
#include <QTextBlock>
#include <QDebug>
#include <QDialog>

class QTextEdit;

class LineNumbers : public QWidget
{
	Q_OBJECT
	Q_PROPERTY( int digitNumbers READ digitNumbers WRITE setDigitNumbers )
	Q_PROPERTY( QColor textColor READ textColor WRITE setTextColor )
        Q_PROPERTY( QColor backgroundColor READ backgroundColor WRITE setBackgroundColor )
public:
        LineNumbers( QTextEdit* );
	void setDigitNumbers( int );
        int digitNumbers() const;
	void setTextColor( const QColor& );
        const QColor& textColor() const;
	void setBackgroundColor( const QColor& );
        const QColor& backgroundColor() const;
	void setExecutedLine(int ligne);
protected:
        virtual void paintEvent( QPaintEvent* );
private:
        QTextEdit* m_textEdit;
	int mDigitNumbers;
	QColor mTextColor;
	QColor mBackgroundColor;
	int m_executedLine;
	int m_currentLine;
        QTextCursor m_cursor;
signals:	
	void digitNumbersChanged();
	void textColorChanged( const QColor& );
        void backgroundColorChanged( const QColor& );
public slots:
	void setDefaultProperties();
};
#endif 

