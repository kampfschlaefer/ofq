
#include "qoscclient.h"

int main()
{
	QOSCClient* c = new QOSCClient( QHostAddress( QHostAddress::LocalHost ), 5282, 0 );

	c->sendData( "/slider", 305 );
	c->sendData( "/slider", 0.3E-4 );
	c->sendData( "/slider", "Bla" );

	QList<QVariant> list;
	list.push_back( 0.5 );
	list.push_back( 10 );
	c->sendData( "/slider", QVariant( list ) );

	//c->sendData( "/quit" );
	return 0;
};

