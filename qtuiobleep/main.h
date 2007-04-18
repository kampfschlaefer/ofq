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

#ifndef MAIN_H
#define MAIN_H

#include <QtGui/QWidget>

#include "tuiobleep_gui.h"

class QOscClient;

class QTuioBleep : public QWidget, private Ui_TuioBleep
{
	Q_OBJECT
	public:
		QTuioBleep( QWidget* );

	public slots:
		void on_angle_valueChanged( double );
		void on_xSlider_valueChanged( int );
		void on_ySlider_valueChanged( int );

		void updateOsc();
	private:
		double _angle;
		double _x;
		double _y;
		QOscClient* client;
};

#endif // MAIN_H

