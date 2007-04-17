#ifndef QOSCCLIENT_H
#define QOSCCLIENT_H

#include <qosctypes.h>

/**
 * will contain the definitions/classes of osc clients
 */

#include <QtNetwork/QHostAddress>

class QOscServer;

/**
 * @brief Client-object for outgoing OSC-Datagrams
 *
 * This class allows to send OSC-messages to a specified host/port.
 */
class QOscClient : public QOscBase
{
	Q_OBJECT
	public:
		/**
		 * @brief An OSC-connection to a specific host/port.
		 *
		 * This creates a new OSC-connection to the specified host/port. Later
		 * the servers host/port can be changed via setAddress();
		 */
		QOscClient( const QHostAddress&, quint16 port, QObject* );
		/// destructor
		~QOscClient();

		/**
		 * @brief ( Re- )Set the host/port to send messages to
		 */
		void setAddress( const QHostAddress&, quint16 port );

		/**
		 * @brief Set a hostaddress for feedback/answers
		 *
		 * If you want answers for your messages you can indicate this by
		 * setting the OSC-Server that is to get these answers.
		 */
		void setAnswerAddress( QOscServer* );

	public slots:
		void sendData( QString, QVariant =QVariant::Invalid );
		void sendData( QString, QList<QVariant> );
	
	private:
		QHostAddress _address;
		quint16 _port;
};

#endif // QOSCCLIENT_H
