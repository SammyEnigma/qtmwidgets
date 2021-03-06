
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

// Qt include.
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QIcon>

// QtMWidgets include.
#include <QtMWidgets/ToolBar>


//
// Widget
//

class Widget
	:	public QWidget
{
public:
	Widget()
	{
		QHBoxLayout * layout = new QHBoxLayout( this );

		QtMWidgets::ToolBar * toolbar =
			new QtMWidgets::ToolBar( this );

		toolbar->addAction( QIcon( ":/img/address-book-new.png" ) );
		toolbar->addAction( QIcon( ":/img/application-exit.png" ) );
		toolbar->addAction( QIcon( ":/img/archive-extract.png" ) );
		toolbar->addAction( QIcon( ":/img/bookmark-new.png" ) );
		toolbar->addAction( QIcon( ":/img/call-start.png" ) );

		layout->addWidget( toolbar );

		resize( 150, 150 );
	}
}; // class Widget



int main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	Widget w;

	w.show();

	return app.exec();
}
