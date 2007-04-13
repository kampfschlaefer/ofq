#ifndef QOSCCLIENT_H
#define QOSCCLIENT_H

#include <qosctypes.h>

/**
 * @file will contain the definitions/classes of osc clients
 */

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtNetwork/QHostAddress>

class QOSCClient_Private;

class QOSCClient : public QObject
{
	Q_OBJECT
	public:
		QOSCClient( const QHostAddress&, quint16 port, QObject* );
		~QOSCClient();

	public slots:
		void sendData( QString, QVariant =QVariant::Invalid );
		void sendData( QString, QList<QVariant> );
	
	private:
		QOSCClient_Private* d;
};

#endif // QOSCCLIENT_H
