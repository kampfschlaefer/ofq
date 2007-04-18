/*
 * Copyright ( C ) 2007 Arnold Krille <arnold@arnoldarts.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or ( at your option ) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

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

