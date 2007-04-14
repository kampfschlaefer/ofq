
#include "qoscclient.h"

int main()
{
	QOscClient* c = new QOscClient( QHostAddress( QHostAddress::LocalHost ), 5282, 0 );

	c->sendData( "/slider", 305 );
	c->sendData( "/slider", 0.3E-4 );
	c->sendData( "/slider", "Bla!" );

	QList<QVariant> list;
	list.push_back( 305 );
	list.push_back( "Testing !" );
	c->sendData( "/slider", QVariant( list ) );
	list.push_back( 0.3E-4 );
	c->sendData( "/slider", QVariant( list ) );

	PathObject* quit = new PathObject( "/quit", QVariant::Invalid, c );
	quit->send();

	//c->sendData( "/quit" );
	return 0;
};

