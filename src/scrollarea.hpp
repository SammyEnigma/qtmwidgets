
/*
	SPDX-FileCopyrightText: 2014-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef QTMWIDGETS__SCROLLAREA_HPP__INCLUDED
#define QTMWIDGETS__SCROLLAREA_HPP__INCLUDED

// QtMWidgets include.
#include "abstractscrollarea.hpp"


namespace QtMWidgets {

//
// ScrollArea
//

class ScrollAreaPrivate;

/*!
	\brief The ScrollArea class provides a scrolling view onto
	another widget.

	A scroll area is used to display the contents of a child widget
	within a frame. If the widget exceeds the size of the frame, the
	view can provide scroll bars so that the entire area of the child
	widget can be viewed. The child widget must be specified with
	setWidget().

	\sa AbstractScrollArea
*/
class ScrollArea
	:	public AbstractScrollArea
{
	Q_OBJECT

	/*!
		\property widgetResizable
		\brief whether the scroll area should resize the view widget

		If this property is set to false (the default), the scroll area
		honors the size of its widget. Regardless of this property, you
		can programmatically resize the widget using widget()->resize(),
		and the scroll area will automatically adjust itself to the new
		size.

		If this property is set to true, the scroll area will
		automatically resize the widget in order to avoid scroll indicators
		where they can be avoided, or to take advantage of extra space.
	*/
	Q_PROPERTY( bool widgetResizable READ widgetResizable WRITE setWidgetResizable )
	/*!
		\property alignment
		\brief the alignment of the scroll area's widget

		A valid alignment is a combination of the following flags:

		\li \c Qt::AlignLeft
		\li \c Qt::AlignHCenter
		\li \c Qt::AlignRight
		\li \c Qt::AlignTop
		\li \c Qt::AlignVCenter
		\li \c Qt::AlignBottom

		By default, the widget stays rooted to the top-left corner of the
		scroll area.
	*/
	Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )

public:
	ScrollArea( QWidget * parent = 0 );
	virtual ~ScrollArea();

	/*!
		\return The scroll area's widget, or 0 if there is none.

		\sa setWidget()
	*/
	QWidget * widget() const;
	/*!
		Sets the scroll area's \a widget.

		The \a widget becomes a child of the scroll area, and will be
		destroyed when the scroll area is deleted or when a new widget is
		set.

		The widget's autoFillBackground property will be set to \c{true}.

		If the scroll area is visible when the \a widget is
		added, you must show() it explicitly.

		Note that You must add the layout of \a widget before you call
		this function; if you add it later, the \a widget will not be
		visible - regardless of when you show() the scroll
		area. In this case, you can also not show() the \a
		widget later.

		\sa widget()
	*/
	void setWidget( QWidget * widget );
	/*!
		Removes the scroll area's widget, and passes ownership of the
		widget to the caller.

		\sa widget()
	 */
	QWidget * takeWidget();

	//! \return widgetResizable property's value.
	bool widgetResizable() const;
	//! Set widgetResizable property's value.
	void setWidgetResizable( bool resizable );

	bool focusNextPrevChild( bool next ) override;

	//! \return alignment property's value.
	Qt::Alignment alignment() const;
	//! Set alignment property's value.
	void setAlignment( Qt::Alignment align );

	/*!
		Scrolls the contents of the scroll area so that the point
		(\a x, \a y) is visible inside the region of the viewport
		with margins specified in pixels by \a xmargin and
		\a ymargin. If the specified point cannot be reached,
		the contents are scrolled to the nearest valid position.
		The default value for both margins is 50 pixels.
	*/
	void ensureVisible( int x, int y, int xmargin = 50, int ymargin = 50 );
	/*!
		Scrolls the contents of the scroll area so that the \a childWidget
		of ScrollArea::widget() is visible inside the viewport with
		margins specified in pixels by \a xmargin and \a ymargin. If the
		specified point cannot be reached, the contents are scrolled to
		the nearest valid position. The default value for both margins is
		50 pixels.
	*/
	void ensureWidgetVisible( QWidget * childWidget,
		int xmargin = 50, int ymargin = 50 );

	QSize sizeHint() const override;

protected:
	explicit ScrollArea( ScrollAreaPrivate * dd, QWidget * parent = 0 );

	bool eventFilter( QObject * o, QEvent * e ) override;
	void resizeEvent( QResizeEvent * e ) override;
	void scrollContentsBy( int dx, int dy ) override;

private:
	Q_DISABLE_COPY( ScrollArea )

	friend class ScrollAreaPrivate;

	inline ScrollAreaPrivate * d_func()
		{ return reinterpret_cast< ScrollAreaPrivate* > ( d.data() ); }
	inline const ScrollAreaPrivate * d_func() const
		{ return reinterpret_cast< const ScrollAreaPrivate* >( d.data() ); }
}; // class ScrollArea

} /* namespace QtMWidgets */

#endif // QTMWIDGETS__SCROLLAREA_HPP__INCLUDED
