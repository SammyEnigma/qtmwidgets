
/*
	SPDX-FileCopyrightText: 2014-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef QTMWIDGETS__DATETIMEPARSER_HPP__INCLUDED
#define QTMWIDGETS__DATETIMEPARSER_HPP__INCLUDED

// Qt include.
#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QVector>

QT_BEGIN_NAMESPACE
class QStyleOption;
QT_END_NAMESPACE


#define DATETIMEPICKER_TIME_MIN QTime( 0, 0, 0, 0 )
#define DATETIMEPICKER_TIME_MAX QTime( 23, 59, 59, 999 )
#define DATETIMEPICKER_DATE_MIN QDate( 100, 1, 1 )
#define DATETIMEPICKER_COMPAT_DATE_MIN QDate( 1752, 9, 14 )
#define DATETIMEPICKER_DATE_MAX QDate( 7999, 12, 31 )
#define DATETIMEPICKER_COMPAT_DATETIME_MIN QDateTime( DATETIMEPICKER_COMPAT_DATE_MIN, DATETIMEPICKER_TIME_MIN )
#define DATETIMEPICKER_DATETIME_MIN QDateTime( DATETIMEPICKER_DATE_MIN, DATETIMEPICKER_TIME_MIN )
#define DATETIMEPICKER_DATETIME_MAX QDateTime( DATETIMEPICKER_DATE_MAX, DATETIMEPICKER_TIME_MAX )
#define DATETIMEPICKER_DATE_INITIAL QDate( 2000, 1, 1 )


namespace QtMWidgets {

//
// Section
//

/*!
	Describes section in DatePicker, TimePicker and DateTimePicker.
*/
class Section {
public:
	enum Type {
		NoSection          = 0x00000,
		AmPmSection        = 0x00001,
		SecondSection      = 0x00002,
		MinuteSection      = 0x00004,
		Hour12Section      = 0x00008,
		Hour24Section      = 0x00010,
		DaySection         = 0x00020,
		DaySectionShort    = 0x00040,
		DaySectionLong     = 0x00080,
		MonthSection       = 0x00100,
		MonthSectionShort  = 0x00200,
		MonthSectionLong   = 0x00400,
		YearSection        = 0x00800,
		YearSection2Digits = 0x01000,

		DaySectionMask = ( DaySection | DaySectionShort | DaySectionLong ),
		MonthSectionMask = ( MonthSection | MonthSectionShort | MonthSectionLong ),
		YearSectionMask = ( YearSection | YearSection2Digits )
	}; // enum Type

	Section();

	explicit Section( Type t );

	//! \return Max width of the section.
	int maxWidth( const QStyleOption & opt ) const;

	//! \return Value of the section for the given \a dt date & time.
	QString value( const QDateTime & dt ) const;

	//! Fill values.
	void fillValues( const QDateTime & current,
		const QDateTime & min, const QDateTime & max,
		bool updateIndex = true );

	//! Type of the section.
	Type type;
	//! Is value prepended with zeroes?
	bool zeroesAdded;
	//! Width of the section.
	int sectionWidth;
	//! Values.
	QVector< QString > values;
	//! Current index.
	int currentIndex;
	//! Offset.
	int offset;
}; // class Section


//
// DateTimeParser
//

/*!
	DateTimeParser is used to parse date & time string format
	used by DatePicker, TimePicker and DateTimePicker.
*/
class DateTimeParser {
public:
	explicit DateTimeParser( QMetaType::Type t );

	virtual ~DateTimeParser();

	/*!
		Parse date & time format.

		If format wasn't parsed correctly then new setting
		will not apply.

		\return Is format parsed correctly.
	*/
	bool parseFormat( const QString & fmt );

	//! Defined sections in format.
	QVector< Section > sections;
	//! Type of the parser.
	QMetaType::Type type;
	//! Format string.
	QString format;
}; // class DateTimeParser

} /* namespace QtMWidgets */

#endif // QTMWIDGETS__DATETIMEPARSER_HPP__INCLUDED
