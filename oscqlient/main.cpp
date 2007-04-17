
#include "qoscclient.h"

int main()
{
	QOscClient* c = new QOscClient( QHostAddress( QHostAddress::LocalHost ), 5282, 0 );

	c->sendData( "/int", 305 );
	c->sendData( "/double", 3E4+5E-2 );
	c->sendData( "/string", "Bla!" );

	QList<QVariant> list;
	list.push_back( 305 );
	list.push_back( "Testing !" );
	c->sendData( "/twoargs", QVariant( list ) );
	list.push_back( 0.3E-4 );
	c->sendData( "/twoargs", QVariant( list ) );

	PathObject* quit = new PathObject( "/quit", QVariant::Invalid, c );
	quit->send();

	//c->sendData( "/quit" );
	return 0;
};

