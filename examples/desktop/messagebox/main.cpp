
/*
	SPDX-FileCopyrightText: 2014-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Qt include.
#include <QApplication>
#include <QObject>
#include <QTimer>

// QtMWidgets include.
#include <QtMWidgets/MessageBox>


class Object
	:	public QObject
{
	Q_OBJECT

public:
	Object()
	{
	}

public slots:
	void start()
	{
		QString translatedTextAboutQtText;
		translatedTextAboutQtText = tr(
			"<p>Qt is a C++ toolkit for cross-platform application "
			"development.</p>"
			"<p>Qt provides single-source portability across all major desktop "
			"operating systems. It is also available for embedded Linux and other "
			"embedded and mobile operating systems.</p>"
			"<p>Qt is available under three different licensing options designed "
			"to accommodate the needs of our various users.</p>"
			"<p>Qt licensed under our commercial license agreement is appropriate "
			"for development of proprietary/commercial software where you do not "
			"want to share any source code with third parties or otherwise cannot "
			"comply with the terms of the GNU LGPL version 3 or GNU LGPL version 2.1.</p>"
			"<p>Qt licensed under the GNU LGPL version 3 is appropriate for the "
			"development of Qt applications provided you can comply with the terms "
			"and conditions of the GNU LGPL version 3.</p>"
			"<p>Qt licensed under the GNU LGPL version 2.1 is appropriate for the "
			"development of Qt applications provided you can comply with the terms "
			"and conditions of the GNU LGPL version 2.1.</p>"
			"<p>Please see <a href=\"http://%2/\">%2</a> "
			"for an overview of Qt licensing.</p>"
			"<p>Copyright (C) %1 Digia Plc and/or its subsidiary(-ies) and other "
			"contributors.</p>"
			"<p>Qt and the Qt logo are trademarks of Digia Plc and/or its subsidiary(-ies).</p>"
			"<p>Qt is a Digia product developed as an open source project. See <a href=\"http://%3/\">%3</a> "
			"for more information.</p>"
			).arg( QStringLiteral( "2014" ),
				  QStringLiteral( "qt.io/licensing" ),
				  QStringLiteral( "qt.io" ) );

		QtMWidgets::MessageBox msg( tr( "About Qt..." ),
			translatedTextAboutQtText );

		msg.exec();

		QApplication::quit();
	}
};


int main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	Object o;

	QTimer::singleShot( 0, &o, &Object::start );

	return app.exec();
}

#include "main.moc"
