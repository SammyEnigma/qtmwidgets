
/*
	SPDX-FileCopyrightText: 2014-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// QtMWidgets include.
#include "scroller.hpp"
#include "fingergeometry.hpp"

// Qt include.
#include <QEvent>
#include <QMouseEvent>
#include <QElapsedTimer>
#include <QVariantAnimation>


namespace QtMWidgets {

//
// ScrollerPrivate
//

class ScrollerPrivate {
public:
	ScrollerPrivate( Scroller * parent, QObject * t )
		:	q( parent )
		,	target( t )
		,	minVelocity( 0 )
		,	maxVelocity( 0 )
		,	startDragDistance( 0 )
		,	scrollingCurve( QEasingCurve::OutCirc )
		,	scrollTime( 3000 )
		,	xVelocity( 0.0 )
		,	yVelocity( 0.0 )
		,	mousePressed( false )
		,	maxPause( 300 )
		,	scrollAnimation( 0 )
		,	distance( 0 )
	{
	}

	void init();

	Scroller * q;
	QObject * target;
	uint minVelocity;
	uint maxVelocity;
	uint startDragDistance;
	QEasingCurve scrollingCurve;
	QElapsedTimer elapsed;
	QPoint pos;
	uint scrollTime;
	qreal xVelocity;
	qreal yVelocity;
	bool mousePressed;
	qint64 maxPause;
	QVariantAnimation * scrollAnimation;
	int distance;
}; // class ScrollerPrivate

void
ScrollerPrivate::init()
{
	const int finger = qMax( FingerGeometry::height(), FingerGeometry::width() );

	minVelocity = finger * 3;
	maxVelocity = finger * 2;
	startDragDistance = finger;

	target->installEventFilter( q );

	scrollAnimation = new QVariantAnimation( q );
	scrollAnimation->setEasingCurve( scrollingCurve );
	scrollAnimation->setDuration( scrollTime );
}


//
// Scroller
//

Scroller::Scroller( QObject * target, QObject * parent )
	:	QObject( parent )
	,	d( new ScrollerPrivate( this, target ) )
{
	d->init();

	connect( d->scrollAnimation, &QVariantAnimation::valueChanged,
		this, &Scroller::_q_animation );

	connect( d->scrollAnimation, &QVariantAnimation::finished,
		this, &Scroller::_q_animationFinished );
}

Scroller::~Scroller()
{
}

uint
Scroller::minRecognizedVelocity() const
{
	return d->minVelocity;
}

void
Scroller::setMinRecognizedVelocity( uint v )
{
	d->minVelocity = v;
}

uint
Scroller::maxReachedVelocity() const
{
	return d->maxVelocity;
}

void
Scroller::setMaxReachedVelocity( uint v )
{
	d->maxVelocity = v;
}

uint
Scroller::dragStartDistance() const
{
	return d->startDragDistance;
}

void
Scroller::setDragStartDistance( uint v )
{
	d->startDragDistance = v;
}

uint
Scroller::scrollTime() const
{
	return d->scrollTime;
}

void
Scroller::setScrollTime( uint v )
{
	if( v > 0 && d->scrollTime != v )
	{
		d->scrollTime = v;

		d->scrollAnimation->setDuration( d->scrollTime );
	}
}

const QEasingCurve &
Scroller::scrollingCurve() const
{
	return d->scrollingCurve;
}

void
Scroller::setScrollingCurve( const QEasingCurve & c )
{
	if( d->scrollingCurve != c )
	{
		d->scrollingCurve = c;

		d->scrollAnimation->setEasingCurve( d->scrollingCurve );
	}
}

bool
Scroller::eventFilter( QObject * obj, QEvent * event )
{
	if( obj == d->target )
	{
		if( event->type() == QEvent::MouseButtonPress )
		{
			QMouseEvent * e = static_cast< QMouseEvent* > ( event );

			d->pos = e->pos();
			d->mousePressed = true;
			d->xVelocity = 0.0;
			d->yVelocity = 0.0;
			d->distance = 0;

			d->scrollAnimation->stop();

			d->elapsed.start();
		}
		else if( event->type() == QEvent::MouseButtonRelease )
		{
			if( d->elapsed.elapsed() <= d->maxPause &&
				(uint) qAbs( d->distance ) >= d->startDragDistance )
			{
				if( qAbs( d->xVelocity ) >= d->minVelocity ||
					qAbs( d->yVelocity ) >= d->minVelocity )
				{
					if( d->maxVelocity > 0 )
					{
						if( qAbs( d->xVelocity ) > d->maxVelocity )
						{
							if( d->xVelocity > 0 )
								d->xVelocity = (qreal) d->maxVelocity;
							else
								d->xVelocity = - (qreal) d->maxVelocity;
						}

						if( qAbs( d->yVelocity ) > d->maxVelocity )
						{
							if( d->yVelocity > 0 )
								d->yVelocity = (qreal) d->maxVelocity;
							else
								d->yVelocity = - (qreal) d->maxVelocity;
						}
					}

					const QPoint newPos = QPoint(
						d->pos.x() + qRound( d->xVelocity * d->scrollTime / 1000 ),
						d->pos.y() + qRound( d->yVelocity * d->scrollTime / 1000 ) );

					d->scrollAnimation->setStartValue( d->pos );
					d->scrollAnimation->setEndValue( newPos );

					emit aboutToStart();

					d->scrollAnimation->start();
				}
			}

			d->elapsed.invalidate();
			d->mousePressed = false;
		}
		else if( event->type() == QEvent::MouseMove )
		{
			if( d->mousePressed )
			{
				QMouseEvent * e = static_cast< QMouseEvent* > ( event );

				const qreal time = (qreal) d->elapsed.elapsed() / 1000.0;

				const QPoint p = e->pos() - d->pos;

				d->distance += p.manhattanLength();

				d->pos = e->pos();

				if( p.manhattanLength() > 5 )
				{
					d->xVelocity = (qreal) p.x() / time;
					d->yVelocity = (qreal) p.y() / time;

					d->elapsed.restart();
				}
			}
		}

		return false;
	}
	else
		return QObject::eventFilter( obj, event );
}

void
Scroller::_q_animation( const QVariant & v )
{
	if( d->scrollAnimation->state() == QAbstractAnimation::Running )
	{
		const QPoint p = v.toPoint() - d->pos;
		d->pos = v.toPoint();

		emit scroll( p.x(), p.y() );
	}
}

void
Scroller::_q_animationFinished()
{
	emit finished();
}

} /* namespace QtMWidgets */
