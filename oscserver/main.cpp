
#include "qoscserver.h"
#include <QtCore/QCoreApplication>

int main( int argc, char** argv )
{
	QCoreApplication* app = new QCoreApplication( argc, argv );

	QOscServer* server = new QOscServer( 5282, app );

	PathObject* quit = new PathObject( "/quit", QVariant::Invalid, server );
	QObject::connect( quit, SIGNAL( data() ), app, SLOT( quit() ) );

	int ret = app->exec();

	delete app;
	return ret;
};

