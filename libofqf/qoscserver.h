#ifndef QOSCSERVER_H
#define QOSCSERVER_H

#include <qosctypes.h>

/*
 * will contain the definitions/classes of osc servers
 */

#include <QtNetwork/QHostAddress>

/**
 * @brief Server-object for incoming OSC-Datagrams
 *
 * Unless you have own objects/code to handle the paths of the incoming
 * packages, you might want to take a look at the PathObject to get the
 * OSC-messages translated into Qt signals.
 */
class QOscServer : public QOscBase
{
	Q_OBJECT
	public:
		/**
		 * Creates an OSC-server that listens on all interfaces on the specified
		 * port for incoming datagrams.
		 */
		QOscServer( quint16 port, QObject* p );
		/**
		 * Creates an OSC-server that listens on the specified address and port
		 * for incoming datagrams.
		 */
		QOscServer( QHostAddress address, quint16 port, QObject* p );
		/// destructor
		~QOscServer();

	signals:
		void data( QString path, QVariant data );

	private slots:
		void readyRead();
	private:
};

#endif // QOSCSERVER_H

