
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2014 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef QTMWIDGETS__PRIVATE__ABSTRACTSCROLLAREA_P_HPP__INCLUDED
#define QTMWIDGETS__PRIVATE__ABSTRACTSCROLLAREA_P_HPP__INCLUDED

// QtMWidgets include.
#include "../abstractscrollarea.hpp"

// Qt include.
#include <QWidget>

QT_BEGIN_NAMESPACE
class QStyleOption;
QT_END_NAMESPACE


namespace QtMWidgets {

//
// ScrollIndicator
//

class ScrollIndicator
	:	public QWidget
{
public:
	ScrollIndicator( const QColor & c, Qt::Orientation o, QWidget * parent );

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

protected:
	void paintEvent( QPaintEvent * );

private:
	void drawIndicator( QPainter * p );

protected:
	friend class AbstractScrollAreaPrivate;
	friend class AbstractScrollArea;

	AbstractScrollArea::ScrollIndicatorPolicy policy;
	int minimumSize;
	int size;
	QPoint pos;
	int width;
	Qt::Orientation orientation;
	bool needPaint;
	QColor color;
}; // class ScrollIndicator


//
// AbstractScrollAreaPrivate
//

class AbstractScrollAreaPrivate {
public:
	explicit AbstractScrollAreaPrivate( AbstractScrollArea * parent )
		:	q( parent )
		,	viewport( 0 )
		,	scrolledAreaSize( 0, 0 )
		,	topLeftCorner( 0, 0 )
		,	top( 0 )
		,	bottom( 0 )
		,	right( 0 )
		,	left( 0 )
		,	leftMouseButtonPressed( false )
		,	horIndicator( 0 )
		,	vertIndicator( 0 )
	{
	}

	void init();
	void layoutChildren( const QStyleOption & opt );
	void normalizePosition();
	void calcIndicators();
	void calcIndicator( Qt::Orientation orient,
		int minSize, int width, bool & needPaint,
		int & indicatorSize, QPoint & indicatorPos );
	void scrollContentsBy( int dx, int dy );

	virtual ~AbstractScrollAreaPrivate()
	{
	}

	AbstractScrollArea * q;
	QColor indicatorColor;
	QWidget * viewport;
	QSize scrolledAreaSize;
	QPoint topLeftCorner;
	int top;
	int bottom;
	int right;
	int left;
	bool leftMouseButtonPressed;
	QPoint mousePos;
	ScrollIndicator * horIndicator;
	ScrollIndicator * vertIndicator;
}; // class AbstractScrollAreaPrivate

} /* namespace QtMWidgets */

#endif // QTMWIDGETS__PRIVATE__ABSTRACTSCROLLAREA_P_HPP__INCLUDED