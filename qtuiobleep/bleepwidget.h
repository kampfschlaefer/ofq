#ifndef BLEEPWIDGET_H
#define BLEEPWIDGET_H

#include <QtGui/QWidget>

class BleepWidget : public QWidget
{
	Q_OBJECT
	public:
		BleepWidget( QWidget* =0 );
		~BleepWidget();

	signals:

	private slots:
		// angle in degree
		void setAngle( double );

		void sendData();

		void newBleep();

	protected:
		void paintEvent( QPaintEvent* );
		void resizeEvent( QResizeEvent* );

		void moveEvent( QMoveEvent* );

		void wheelEvent( QWheelEvent* );
		void mouseMoveEvent( QMouseEvent* );
		void contextMenuEvent( QContextMenuEvent* );
		void mouseReleaseEvent( QMouseEvent* );

	private:
		QRect rect;
		QMatrix matrix;

		double angle;

		int me;
};

#endif // BLEEPWIDGET_H

