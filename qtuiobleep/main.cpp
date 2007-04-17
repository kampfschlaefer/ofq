
#include "main.h"
#include "qoscclient.h"

#include <QtCore/QDebug>
#include <QtGui/QApplication>

QTuioBleep::QTuioBleep( QWidget* p ) : QWidget( p ) {
	setupUi( this );
	client = new QOscClient( QHostAddress( QHostAddress::LocalHost ), 3333, this );
}
void QTuioBleep::on_angle_valueChanged( double d ) { _angle = d; updateOsc(); }
void QTuioBleep::on_xSlider_valueChanged( int d ) { _x = d; updateOsc(); }
void QTuioBleep::on_ySlider_valueChanged( int d ) { _y = d; updateOsc(); }

void QTuioBleep::updateOsc() {
	client->sendData( "/tuio/2Dobj", QList<QVariant>() << "set" << 1 << 1 << _x /* x */<< _y /* y */ << _angle/* angle */ << 0.0 /* x-move */ << 0.0 /* y-move */ << 0.0 /* angle-move */ << 0.0 /* accel */ << 0.0 /* rotation-accel */ );
}

int main( int argc, char** argv )
{
	QApplication* app = new QApplication( argc, argv );

	QTuioBleep* w = new QTuioBleep( 0 );
	w->show();

	return app->exec();
};

