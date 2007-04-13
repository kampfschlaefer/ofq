
#include "qosctypes.h"

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QDebug>

void fillQByteArrayUp( QByteArray& in ) {
	while ( in.length() % 4 != 0 )
		in.append( char( 0 ) );
}

QByteArray fromString( QString str ) {
	QByteArray out = str.toUtf8();
	while ( out.length() % 4 != 0 )
		out.append( char( 0 ) );
	return out;
}

QByteArray reverseQByteArray( QByteArray in ) {
	QByteArray out;
	for ( int i=0; i<in.size(); ++i )
		out.prepend( in[ i ] );
	return out;
}

QByteArray fromInt32( qint32 i ) {
	QByteArray tmp( ( char* )static_cast<void*>( &i ), 4 );
	return reverseQByteArray( tmp );
}
QByteArray fromDouble( float f ) {
	QByteArray tmp( ( char* )static_cast<void*>( &f ), 4 );
	return reverseQByteArray( tmp );
}

void oscMessageParseArgs( QVariant data, QString& argtypes, QByteArray& arguments ) {
	if ( data.type() == QVariant::Int ) {
		argtypes += "i";
		arguments = arguments + fromInt32( data.toInt() );
	}
	if ( data.type() == QVariant::Double ) {
		argtypes += "f";
		arguments += fromDouble( data.toDouble() );
	}
	if ( data.type() == QVariant::String ) {
		argtypes += "s";
		arguments += fromString( data.toString() );
	}
	if ( data.type() == QVariant::List ) {
		QList<QVariant> list = data.toList();
		foreach( QVariant v, list )
			oscMessageParseArgs( v, argtypes, arguments );
	}
}

QByteArray oscMessage( QString path, QVariant arg ) {
	QString argtypes( "," );
	QByteArray arguments;

	oscMessageParseArgs( arg, argtypes, arguments );

	QByteArray out = fromString( path );
	out.append( fromString( argtypes ) );
	out.append( arguments );
	return out;
}

