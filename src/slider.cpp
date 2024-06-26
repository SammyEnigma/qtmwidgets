
/*
	SPDX-FileCopyrightText: 2014-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// QtMWidgets include.
#include "slider.hpp"
#include "color.hpp"
#include "private/drawing.hpp"

// Qt include.
#include <QPainter>
#include <QStyle>
#include <QPalette>
#include <QMouseEvent>


namespace QtMWidgets {

//
// SliderPrivate
//

class SliderPrivate {
public:
	SliderPrivate( Slider * parent )
		:	q( parent )
		,	radius( 0 )
		,	grooveHeight( 2 )
		,	pressedControl( QStyle::SC_None )
		,	clickOffset( 0 )
	{
	}

	void init();
	QRect handleRect() const;
	int pixelPosToRangeValue( int p ) const;
	inline int pick( const QPoint & pt ) const;
	QRect grooveRect() const;
	QRect grooveHighlightedRect( const QRect & sh, const QRect & gr ) const;

	Slider * q;
	int radius;
	int grooveHeight;
	QStyle::SubControl pressedControl;
	int clickOffset;
	QColor highlightColor;
}; // class SliderPrivate;

void
SliderPrivate::init()
{
	radius = q->fontMetrics().ascent();

	QSizePolicy sp( QSizePolicy::Expanding, QSizePolicy::Fixed );

	if( q->orientation() == Qt::Vertical )
		sp.transpose();

	q->setSizePolicy( sp );

	highlightColor = q->palette().color( QPalette::Highlight );
}

QRect
SliderPrivate::handleRect() const
{
	const QRect cr = q->contentsRect();

	int hx = 0, hy = 0;

	if( q->orientation() == Qt::Vertical )
	{
		hx = cr.topLeft().x() + cr.width() / 2 - radius + 1;
		hy = QStyle::sliderPositionFromValue( q->minimum(), q->maximum(),
			q->sliderPosition(), cr.height() - radius * 2 - 2,
			q->invertedAppearance() ) + 1;
	}
	else
	{
		hx = QStyle::sliderPositionFromValue( q->minimum(), q->maximum(),
			q->sliderPosition(), cr.width() - radius * 2 - 2,
			q->invertedAppearance() ) + 1;
		hy = cr.topLeft().y() + cr.height() / 2 - radius + 1;
	}

	return QRect( hx, hy, radius * 2, radius * 2 );
}

int
SliderPrivate::pixelPosToRangeValue( int p ) const
{
	const QRect gr = grooveRect();

	int sliderMin = 0, sliderMax = 0;

	if( q->orientation() == Qt::Horizontal )
	{
		sliderMin = gr.x();
		sliderMax = gr.right() - 2 * radius;
	}
	else
	{
		sliderMin = gr.y();
		sliderMax = gr.bottom() - 2 * radius;
	}

	return QStyle::sliderValueFromPosition( q->minimum(), q->maximum(),
		p - sliderMin, sliderMax - sliderMin, q->invertedAppearance() );
}

inline int
SliderPrivate::pick( const QPoint & pt ) const
{
	return q->orientation() == Qt::Horizontal ? pt.x() : pt.y();
}

QRect
SliderPrivate::grooveRect() const
{
	const QRect cr = q->contentsRect();

	int gx = 0, gy = 0, gw = 0, gh = 0;

	if( q->orientation() == Qt::Vertical )
	{
		gx = cr.topLeft().x() + ( cr.width() - grooveHeight ) / 2;
		gy = cr.topLeft().y() + 1;
		gw = grooveHeight;
		gh = cr.height() - 2;
	}
	else
	{
		gx = cr.topLeft().x() + 1;
		gy = cr.topLeft().y() + ( cr.height() - grooveHeight ) / 2;
		gw = cr.width() - 2;
		gh = grooveHeight;
	}

	return QRect( gx, gy, gw, gh );
}

QRect
SliderPrivate::grooveHighlightedRect( const QRect & sh, const QRect & gr ) const
{
	int grhw = 0, grhh = 0;

	QRect grh;

	if( !q->invertedAppearance() )
	{
		if( q->orientation() == Qt::Vertical )
			grhh = gr.height() - sh.y() - radius;
		else
			grhw = gr.width() - sh.x() - radius;

		grh = gr.marginsRemoved( QMargins( 0, 0, grhw, grhh ) );
	}
	else
	{
		if( q->orientation() == Qt::Vertical )
			grhh = sh.y() + radius;
		else
			grhw = sh.x() + radius;

		grh = gr.marginsRemoved( QMargins( grhw, grhh, 0, 0 ) );
	}

	return grh;
}


//
// Slider
//

Slider::Slider( QWidget * parent )
	:	QAbstractSlider( parent )
	,	d( new SliderPrivate( this ) )
{
	setOrientation( Qt::Vertical );
	d->init();
}

Slider::Slider( Qt::Orientation orientation, QWidget * parent )
	:	QAbstractSlider( parent )
	,	d( new SliderPrivate( this ) )
{
	setOrientation( orientation );
	d->init();
}

Slider::~Slider()
{
}

int
Slider::handleRadius() const
{
	return d->radius;
}

void
Slider::setHandleRadius( int r )
{
	if( d->radius != r && r >= d->grooveHeight )
	{
		d->radius = r;
		updateGeometry();
		update();
	}
}

const QColor &
Slider::highlightColor() const
{
	return d->highlightColor;
}

void
Slider::setHighlightColor( const QColor & c )
{
	if( d->highlightColor != c )
	{
		d->highlightColor = c;
		update();
	}
}

int
Slider::grooveHeight() const
{
	return d->grooveHeight;
}

void
Slider::setGrooveHeight( int h )
{
	if( h > 0 && h != d->grooveHeight )
	{
		d->grooveHeight = h;

		updateGeometry();
		update();
	}
}

QSize
Slider::sizeHint() const
{
	return minimumSizeHint();
}

QSize
Slider::minimumSizeHint() const
{
	const int minWidth = d->radius * 10 + 3;
	const int height = d->radius * 2 + 3;

	int w = minWidth;
	int h = height;

	if( orientation() == Qt::Vertical )
	{
		w = height;
		h = minWidth;
	}

	return QSize( w, h );
}

void
Slider::paintEvent( QPaintEvent * )
{
	const QRect sh = d->handleRect();
	const QRect gr = d->grooveRect();
	const QRect grh = d->grooveHighlightedRect( sh, gr );

	QPainter p( this );

	const QColor grooveColor = palette().color( QPalette::Dark );

	p.setPen( grooveColor );
	p.setBrush( grooveColor );

	p.drawRect( gr );

	p.setPen( d->highlightColor );
	p.setBrush( d->highlightColor );

	p.drawRect( grh );

	p.setRenderHint( QPainter::Antialiasing );
	drawSliderHandle( &p, sh, d->radius, d->radius,
		palette().color( QPalette::Shadow ),
		palette().color( QPalette::Base ) );
}

void
Slider::mousePressEvent( QMouseEvent * e )
{
	if( maximum() == minimum() || ( e->buttons() ^ e->button() ) )
	{
		e->ignore();
		return;
	}

	if( e->button() == Qt::LeftButton )
	{
		e->accept();
		const QRect hr = d->handleRect();

		if( hr.contains( e->pos() ) )
		{
			d->pressedControl = QStyle::SC_SliderHandle;
			setRepeatAction( SliderNoAction );
			triggerAction( SliderMove );
			update();
		}
		else
		{
			d->pressedControl = QStyle::SC_SliderGroove;
			SliderAction action = SliderNoAction;

			const int pressValue =
				d->pixelPosToRangeValue( d->pick( e->pos() ) - 2 * d->radius );

			if( pressValue > value() )
				action = SliderPageStepAdd;
			else if( pressValue < value() )
				action = SliderPageStepSub;
			if( action )
			{
				triggerAction( action );
				setRepeatAction( action );
			}
		}

		if( d->pressedControl == QStyle::SC_SliderHandle )
		{
			d->clickOffset = d->pick( e->pos() - hr.topLeft() );
			setRepeatAction( SliderNoAction );
			setSliderDown( true );
		}
	}
	else
		e->ignore();
}

void
Slider::mouseReleaseEvent( QMouseEvent * e )
{
	if( d->pressedControl == QStyle::SC_None || e->buttons() )
	{
		e->ignore();
		return;
	}

	e->accept();
	QStyle::SubControl oldPressed = QStyle::SubControl( d->pressedControl );
	d->pressedControl = QStyle::SC_None;
	setRepeatAction( SliderNoAction );
	if( oldPressed == QStyle::SC_SliderHandle )
		setSliderDown( false );
	update();
}

void
Slider::mouseMoveEvent( QMouseEvent * e )
{
	if( d->pressedControl != QStyle::SC_SliderHandle )
	{
		e->ignore();
		return;
	}

	e->accept();

	const int newPosition = d->pixelPosToRangeValue(
		d->pick( e->pos() ) - d->clickOffset );

	setSliderPosition( newPosition );
}

} /* namespace QtMWidgets */
