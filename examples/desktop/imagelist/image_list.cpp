
/*
	SPDX-FileCopyrightText: 2014-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#include "image_list.hpp"

// Qt include.
#include <QPainter>
#include <QLinearGradient>

// QtMWidgets include.
#include <QtMWidgets/Color>


//
// ImageListPrivate
//

class ImageListPrivate {
public:
	ImageListPrivate( const QSize & maxSize, ImageList * parent )
		:	q( parent )
		,	borderWidth( 5 )
		,	maxImageSize( QSize( maxSize.width() - 2 * borderWidth,
				maxSize.height() - 2 * borderWidth ) )
	{
	}

	//! Init.
	void init();

	//! Parent.
	ImageList * q;
	//! Border width.
	int borderWidth;
	//! Maximum image size.
	QSize maxImageSize;
}; // class ImageListPrivate

void
ImageListPrivate::init()
{
	q->setSpacing( borderWidth );
}


//
// ImageList
//


ImageList::ImageList( const QSize maxImageSize, QWidget * parent )
	:	QtMWidgets::AbstractListView< QImage > ( parent )
	,	d( new ImageListPrivate( maxImageSize, this ) )
{
	d->init();
}

ImageList::~ImageList()
{
}

QSize
ImageList::maxImageSize() const
{
	return d->maxImageSize;
}

void
ImageList::drawRow( QPainter * painter,
	const QRect & rect, int row )
{
	QColor background = palette().color( QPalette::Button );

	QLinearGradient g( QPointF( 0.0, 0.0 ), QPointF( 1.0, 0.0 ) );
	g.setCoordinateMode( QGradient::ObjectBoundingMode );
	g.setColorAt( 0.0, background );
	g.setColorAt( 1.0, QtMWidgets::lighterColor( background, 75 ) );

	QColor border = palette().color( QPalette::Dark );

	painter->setPen( border );
	painter->setBrush( g );

	const QImage & image = model()->data( row );

	const int x = rect.x() + ( rect.width() - image.width() ) / 2;
	const int y = rect.y();

	const QRect r( x, y,
		image.width() + 2 * d->borderWidth,
		image.height() + 2 * d->borderWidth );

	painter->drawRect( r );
	painter->drawRect( r.adjusted( d->borderWidth - 1, d->borderWidth - 1,
		- d->borderWidth, - d->borderWidth ) );

	if( !image.isNull() )
		painter->drawImage( QPoint( x + d->borderWidth, y + d->borderWidth ),
			image );
}

int
ImageList::rowHeightForWidth( int row, int width ) const
{
	Q_UNUSED( width )

	return model()->data( row ).height() + 2 * d->borderWidth;
}
