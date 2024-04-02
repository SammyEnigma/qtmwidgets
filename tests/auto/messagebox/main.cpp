
/*
	SPDX-FileCopyrightText: 2014-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Qt include.
#include <QObject>
#include <QtTest/QtTest>
#include <QSharedPointer>
#include <QTimer>
#include <QAbstractButton>

// QtMWidgets include.
#include <QtMWidgets/MessageBox>


class TestMessageBox
	:	public QObject
{
	Q_OBJECT

private slots:

	void testMessageBox()
	{
		m_box.reset( new QtMWidgets::MessageBox( QStringLiteral( "MessageBox" ),
			QStringLiteral( "Text." ) ) );

		m_box->setTextFormat( Qt::PlainText );

		QVERIFY( m_box->textFormat() == Qt::PlainText );

		auto * ok = m_box->addButton( QStringLiteral( "OK 2" ), QtMWidgets::MessageBox::AcceptRole );

		const auto accept = m_box->buttons( QtMWidgets::MessageBox::AcceptRole );

		QVERIFY( accept.size() == 2 );

		QVERIFY( m_box->buttonRole( ok ) == QtMWidgets::MessageBox::AcceptRole );

		auto * cancel = m_box->addButton( QStringLiteral( "Cancel" ),
			QtMWidgets::MessageBox::RejectRole );

		auto reject = m_box->buttons( QtMWidgets::MessageBox::RejectRole );

		QVERIFY( reject.size() == 1 );
		QVERIFY( reject.constFirst() == cancel );

		QVERIFY( m_box->buttonRole( cancel ) == QtMWidgets::MessageBox::RejectRole );

		QVERIFY( m_box->buttons().size() == 3 );

		m_box->removeButton( cancel );

		reject = m_box->buttons( QtMWidgets::MessageBox::RejectRole );

		QVERIFY( reject.isEmpty() );

		QVERIFY( m_box->text() == QStringLiteral( "Text." ) );

		const auto text = QStringLiteral( "Text in the message box." );

		m_box->setText( text );

		QVERIFY( m_box->text() == text );

		QSignalSpy spy( m_box.data(), &QtMWidgets::MessageBox::buttonClicked );

		connect( m_box.data(), &QtMWidgets::MessageBox::buttonClicked, this,
			[&] ( QAbstractButton * b )
			{
				QVERIFY( b == ok );
			} );

		QTimer::singleShot( 1000, this,
			[&] ()
			{
				QTest::mouseClick( ok, Qt::LeftButton, {}, ok->rect().center() );
			} );

		const auto ret = m_box->exec();

		QVERIFY( ret == QDialog::Accepted );

		QVERIFY( spy.count() == 1 );

		QVERIFY( m_box->clickedButton() == ok );
	}

private:
	QSharedPointer< QtMWidgets::MessageBox > m_box;
};


QTEST_MAIN( TestMessageBox )

#include "main.moc"
