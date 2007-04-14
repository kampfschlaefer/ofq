
#include "qoscserver.h"

#include <QtCore/QDebug>
#include <QtNetwork/QUdpSocket>

QOscServer::QOscServer( quint16 port, QObject* p )
	: QOscBase( p )
{
	qDebug() << "QOscServer::QOscServer(" << port << "," << p << ")";
	socket->bind( QHostAddress::Any, port );
	connect( socket, SIGNAL( readyRead() ), this, SLOT( readyRead() ) );
}
QOscServer::QOscServer( QHostAddress address, quint16 port, QObject* p )
	: QOscBase( p )
{
	qDebug() << "QOscServer::QOscServer(" << address << "," << port << "," << p << ")";
	socket->bind( address, port );
}

QOscServer::~QOscServer() {
	qDebug() << "QOscServer::~QOscServer()";
}

#define BUFFERSIZE 255

void QOscServer::readyRead() {
	qDebug() << "QOscServer::readyRead()";
	while ( socket->hasPendingDatagrams() ) {
		QByteArray data( BUFFERSIZE, char( 0 ) );
		//data.resize( BUFFERSIZE );
		int size = socket->readDatagram( data.data(), BUFFERSIZE );
		qDebug() << " read" << size << "(" << data.size() << ") bytes:" << data;

		//for ( int i=0; i<size; ++i )
		//	qDebug() << i << "\t" << static_cast<quint8*>( static_cast<void*>( data.data() ) )[ i ];
		QString path;
		QString args;
		QVariant arguments;

		int i=0;
		if ( data[ i ] == '/' ) {

			for ( ; i<size && data[ i ] != char( 0 ); ++i )
				path += data[ i ];

			while ( data[ i ] != ',' ) ++i;
			++i;
			while ( data[ i ] != char( 0 ) )
				args += data[ i++ ];

			if ( ! args.isEmpty() ) {
				QList<QVariant> list;

				foreach( QChar type, args ) {
					while ( i%4 != 0 ) ++i;
					//qDebug() << i << "\ttrying to convert to" << type;

					QByteArray tmp = data.right( data.size()-i );
					QVariant value;
					if ( type == 's' ) {
						QString s = toString( tmp );
						value = s;
						i += s.size();
					}
					if ( type == 'i' ) {
						value = toInt32( tmp );
						i+=4;
					}
					if ( type == 'f' ) {
						value = toFloat( tmp );
						i+=4;
					}
					//qDebug() << " got" << value;

					if ( args.size() > 1 )
						list.append( value );
					else
						arguments = value;
				}

				if ( args.size() > 1 )
					arguments = list;
			}
		}
		qDebug() << "path seems to be" << path << "args are" << args << ":" << arguments;
	}
}

