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

