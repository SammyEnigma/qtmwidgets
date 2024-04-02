
/*
	SPDX-FileCopyrightText: 2014-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef QTMWIDGETS__MESSAGEBOX_HPP__INCLUDED
#define QTMWIDGETS__MESSAGEBOX_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QAbstractButton;
QT_END_NAMESPACE


namespace QtMWidgets {

//
// MessageBox
//

class MessageBoxPrivate;

/*!
	Message box.

	\note Message box always has "OK" button.
*/
class MessageBox
	:	public QDialog
{
	Q_OBJECT

	/*!
		\property text

		Text in message box.
	*/
	Q_PROPERTY( QString text READ text WRITE setText )
	/*!
		\property textFormat

		Text format.

		By default, this property is Qt::AutoText.
	*/
	Q_PROPERTY( Qt::TextFormat textFormat READ textFormat WRITE setTextFormat )

signals:
	//! Button clicked.
	void buttonClicked( QAbstractButton * button );

public:
	//! Button's role.
	enum ButtonRole {
		//! The button is invalid.
		InvalidRole = -1,
		//! Clicking the button causes the dialog to be accepted (e.g. OK).
		AcceptRole = 0,
		//! Clicking the button causes the dialog to be rejected (e.g. Cancel).
		RejectRole = 1
	}; // enume ButtonRole

	Q_ENUM( ButtonRole )

public:
	MessageBox( const QString & title,
		const QString & text, QWidget * parent = 0 );
	virtual ~MessageBox();

	//! Add button.
	void addButton( QAbstractButton * button, ButtonRole role );
	//! Add button.
	QAbstractButton * addButton( const QString & text, ButtonRole role );
	//! \return Button for the given \a role role.
	QList< QAbstractButton* > buttons( ButtonRole role ) const;
	//! \return Role of the given \a button button.
	ButtonRole buttonRole( QAbstractButton * button ) const;
	//! \return All buttons.
	const QList< QAbstractButton* > & buttons() const;
	//! \return Clicked button.
	QAbstractButton * clickedButton() const;
	//! Remove button.
	void removeButton( QAbstractButton * button );

	//! \return Text.
	QString text() const;
	//! Set text.
	void setText( const QString & t );

	//! \return Text format.
	Qt::TextFormat textFormat() const;
	//! Set text format.
	void setTextFormat( Qt::TextFormat fmt );

private slots:
	void _q_clicked();

private:
	Q_DISABLE_COPY( MessageBox )

	QScopedPointer< MessageBoxPrivate > d;
};

} /* namespace QtMWidgets */

#endif // QTMWIDGETS__MESSAGEBOX_HPP__INCLUDED
