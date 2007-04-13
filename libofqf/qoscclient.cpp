
#include "qoscclient.h"
//#include "qoscclient.moc"

#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtNetwork/QUdpSocket>

#include "qosctypes.h"

#include <lo/lo.h>

class QOSCClient_Private
{
	friend class QOSCClient;

	QUdpSocket* socket;
	QHostAddress address;
	quint16 port;
};

QOSCClient::QOSCClient( const QHostAddress& address, quint16 port, QObject* p )
	: QObject( p )
	, d( new QOSCClient_Private() )
{
	qDebug() << "QOSCClient::QOSCClient(" << address << "," << port << "," << p << ")";
	d->socket = new QUdpSocket( this );
	d->address = address;
	d->port = port;
}

QOSCClient::~QOSCClient() {
	qDebug() << "QOSCClient::~QOSCClient()";
	delete d;
}

void QOSCClient::sendData( QString path, QVariant data ) {
	qDebug() << "QOSCClient::sendData(" << path << "," << data << ")";
	/*QByteArray tmp = oscMessage( path, data );
	qDebug() << " length:" << tmp.length();
	d->socket->writeDatagram( tmp, d->address, d->port );*/
	lo_message msg = lo_message_new();
	if ( data.type() == QVariant::Int )
		lo_message_add_int32( msg, data.toInt() );
	if ( data.type() == QVariant::Double )
		lo_message_add_float( msg, data.toDouble() );
	if ( data.type() == QVariant::String )
		lo_message_add_string( msg, data.toString().toStdString().c_str() );
	size_t charsize=0;
	void* chars = lo_message_serialise( msg, path.toStdString().c_str(), 0, &charsize );
	qDebug() << " osc-message at" << chars << " length is" << charsize;
	QByteArray out = oscMessage( path, data );
	qDebug() << " own message has size" << out.size();
	for ( int i=0; i<qMax( int( charsize ), out.size() ); ++i ) {
		qDebug() << "  byte" << i << "\t" << static_cast<quint8*>( chars )[ i ] /*<< "\"" << static_cast<char*>( chars )[ i ] << "\""*/ << "\t :" << quint8( out[ i ] ) << "\t\"" << out[ i ] << "\"";
	}
	//QByteArray out( static_cast<char*>( chars ), charsize );
	d->socket->writeDatagram( out, d->address, d->port );
}
void QOSCClient::sendData( QString path, QList<QVariant> data ) {
	qDebug() << "QOSCClient::sendData(" << path << "," << data << ")";
}

