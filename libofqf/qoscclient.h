#ifndef QOSCCLIENT_H
#define QOSCCLIENT_H

#include <qosctypes.h>

/**
 * will contain the definitions/classes of osc clients
 */

#include <QtNetwork/QHostAddress>

/**
 * @brief Client-object for outgoing OSC-Datagrams
 */
class QOscClient : public QOscBase
{
	Q_OBJECT
	public:
		QOscClient( const QHostAddress&, quint16 port, QObject* );
		~QOscClient();

		void setAddress( const QHostAddress&, quint16 port );

	public slots:
		void sendData( QString, QVariant =QVariant::Invalid );
		void sendData( QString, QList<QVariant> );
	
	private:
		QHostAddress _address;
		quint16 _port;
};

#endif // QOSCCLIENT_H
