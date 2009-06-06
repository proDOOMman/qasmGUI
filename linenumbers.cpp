// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#include "linenumbers.h"

LineNumbers::LineNumbers( QTextEdit *edit)
        : QWidget( (QWidget *)edit ), m_textEdit( edit )
{
        setAutoFillBackground( true );
	connect( m_textEdit->document()->documentLayout(), SIGNAL( update( const QRectF& ) ), this, SLOT( update() ) );
	connect( m_textEdit->verticalScrollBar(), SIGNAL( valueChanged( int ) ), this, SLOT( update() ) );
	m_executedLine = 0;
	setDefaultProperties();	
        setMouseTracking( true );
}

void LineNumbers::paintEvent( QPaintEvent* )
{
	int contentsY = m_textEdit->verticalScrollBar()->value();
	qreal pageBottom = contentsY + m_textEdit->viewport()->height();
	int m_lineNumber = 1;
	const QFontMetrics fm = fontMetrics();
        const int ascent = fontMetrics().ascent() +1;
        QPainter p( this );
	for ( QTextBlock block = m_textEdit->document()->begin(); block.isValid(); block = block.next(), m_lineNumber++ )
	{
		QTextLayout* layout = block.layout();
		const QRectF boundingRect = layout->boundingRect();
		QPointF position = layout->position();
		if ( position.y() +boundingRect.height() < contentsY )
			continue;
		if ( position.y() > pageBottom )
			break;
		const QString txt = QString::number( m_lineNumber );
		if( m_lineNumber == m_executedLine )
		{
			int centreV = qRound( position.y() ) -contentsY + 8;
			p.setBrush( Qt::blue );
			float x = width()-1;
			const QPointF points[7] = {
        			QPointF(x, centreV),
        			QPointF(x-9, centreV-8),
        			QPointF(x-9, centreV-4),
        			QPointF(x-15, centreV-4),
        			QPointF(x-15, centreV+4),
        			QPointF(x-9, centreV+4),
        			QPointF(x-9, centreV+8),
    			};

    			p.drawPolygon(points, 7);
		}
		else
                        p.drawText( width() -fm.width( txt ) - 2, qRound( position.y() ) -contentsY +ascent, txt );
        }
	p.end();
}

void LineNumbers::setDigitNumbers( int i )
{
	if ( i == mDigitNumbers )
		return;
	mDigitNumbers = i;
        setFixedWidth( fontMetrics().width( "0" ) * (i) + 22 );
	emit digitNumbersChanged();
}

int LineNumbers::digitNumbers() const
{
	return mDigitNumbers;
}

void LineNumbers::setTextColor( const QColor& c )
{
	if ( c == mTextColor )
		return;
	mTextColor = c;
	QPalette p( palette() );
	p.setColor( foregroundRole(), mTextColor );
	setPalette( p );
	emit textColorChanged( mTextColor );
}

const QColor& LineNumbers::textColor() const
{
	return mTextColor;
}

void LineNumbers::setBackgroundColor( const QColor& c )
{
	if ( c == mBackgroundColor )
		return;
	mBackgroundColor = c;
	QPalette p( palette() );
	p.setColor( backgroundRole(), mBackgroundColor );
	setPalette( p );
	emit backgroundColorChanged( mBackgroundColor );
}

const QColor& LineNumbers::backgroundColor() const
{
	return mBackgroundColor;
}

void LineNumbers::setDefaultProperties()
{
	setFont( m_textEdit->font() );
        setBackgroundColor( QColor( Qt::lightGray ) );
        setTextColor( QColor( Qt::black ) );
        setDigitNumbers( 3 );
}
