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

