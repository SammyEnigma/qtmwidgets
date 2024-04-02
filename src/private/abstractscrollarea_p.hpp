
/*
	SPDX-FileCopyrightText: 2014-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef QTMWIDGETS__PRIVATE__ABSTRACTSCROLLAREA_P_HPP__INCLUDED
#define QTMWIDGETS__PRIVATE__ABSTRACTSCROLLAREA_P_HPP__INCLUDED

// QtMWidgets include.
#include "../abstractscrollarea.hpp"

// Qt include.
#include <QWidget>

QT_BEGIN_NAMESPACE
class QStyleOption;
class QTimer;
class QVariantAnimation;
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

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

protected:
	void paintEvent( QPaintEvent * ) override;

private:
	void drawIndicator( QPainter * p, const QColor & c );

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
	bool animate;
	int alpha;
}; // class ScrollIndicator


//
// BlurEffect
//

class BlurEffect
	:	public QWidget
{
public:
	BlurEffect( const QColor & c, Qt::Orientation o, QWidget * parent );

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

protected:
	void paintEvent( QPaintEvent * ) override;

private:
	void drawBlur( QPainter * p, const QColor & c );

protected:
	friend class AbstractScrollAreaPrivate;
	friend class AbstractScrollArea;

	AbstractScrollArea::BlurPolicy policy;
	Qt::Orientation orientation;
	QColor color;
	int pressure;
	int darkBlurWidth;
	qreal maxPressure;
}; // class BlurEffect


class Scroller;

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
		,	animationTimer( 0 )
		,	startBlurAnimTimer( 0 )
		,	animationTimeout( 100 )
		,	animationAlphaDelta( 25 )
		,	scroller( 0 )
		,	horBlur( 0 )
		,	vertBlur( 0 )
		,	horBlurAnim( 0 )
		,	vertBlurAnim( 0 )
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
	void makeBlurEffectIfNeeded();
	void animateHiddingBlurEffect();
	void stopAnimatingBlurEffect();
	void animateScrollIndicators();
	void stopScrollIndicatorsAnimation();

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
	QTimer * animationTimer;
	QTimer * startBlurAnimTimer;
	int animationTimeout;
	int animationAlphaDelta;
	Scroller * scroller;
	BlurEffect * horBlur;
	BlurEffect * vertBlur;
	QVariantAnimation * horBlurAnim;
	QVariantAnimation * vertBlurAnim;
}; // class AbstractScrollAreaPrivate

} /* namespace QtMWidgets */

#endif // QTMWIDGETS__PRIVATE__ABSTRACTSCROLLAREA_P_HPP__INCLUDED
