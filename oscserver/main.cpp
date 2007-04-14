
#include "qoscserver.h"
#include <QtGui/QtGui>

int main( int argc, char** argv )
{
	QApplication* app = new QApplication( argc, argv );

	QOscServer* server = new QOscServer( 5282, app );

	QPushButton* btnQuit = new QPushButton( "Quit", 0 );
	QObject::connect( btnQuit, SIGNAL( clicked() ), app, SLOT( quit() ) );
	btnQuit->show();

	PathObject* quit = new PathObject( "/quit", QVariant::Invalid, server );
	QObject::connect( quit, SIGNAL( data() ), btnQuit, SLOT( click() ) );

	int ret = app->exec();

	delete app;
	return ret;
};

