
#include "qoscclient.h"
//#include "qoscclient.moc"

#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtNetwork/QUdpSocket>

#include <lo/lo.h>

QOscClient::QOscClient( const QHostAddress& address, quint16 port, QObject* p )
	: QOscBase( p )
	, _address( address )
	, _port( port )
{
	qDebug() << "QOscClient::QOscClient(" << address << "," << port << "," << p << ")";
}

QOscClient::~QOscClient() {
	qDebug() << "QOscClient::~QOscClient()";
}

void QOscClient::setAddress( const QHostAddress& address, quint16 port ) {
	_address = address;
	_port = port;
}

void QOscClient::sendData( QString path, QVariant data ) {
	//qDebug() << "QOscClient::sendData(" << path << "," << data << ")";
	/*lo_message msg = lo_message_new();
	if ( data.type() == QVariant::Int )
		lo_message_add_int32( msg, data.toInt() );
	if ( data.type() == QVariant::Double )
		lo_message_add_float( msg, data.toDouble() );
	if ( data.type() == QVariant::String )
		lo_message_add_string( msg, data.toString().toStdString().c_str() );
	size_t charsize=0;
	void* chars = lo_message_serialise( msg, path.toStdString().c_str(), 0, &charsize );*/
	//qDebug() << " osc-message at" << chars << " length is" << charsize;
	QByteArray out = oscMessage( path, data );
	//qDebug() << " own message has size" << out.size();
	//for ( int i=0; i<qMax( int( charsize ), out.size() ); ++i )
	//	qDebug() << "  byte" << i << "\t" << static_cast<quint8*>( chars )[ i ] /*<< "\"" << static_cast<char*>( chars )[ i ] << "\""*/ << "\t :" << quint8( out[ i ] ) << "\t\"" << out[ i ] << "\"";
	socket()->writeDatagram( out, _address, _port );
}
void QOscClient::sendData( QString path, QList<QVariant> data ) {
	//qDebug() << "QOscClient::sendData(" << path << "," << data << ")";
	QByteArray out = oscMessage( path, data );
	socket()->writeDatagram( out, _address, _port );
}

