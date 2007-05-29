
#include "bleepwidget.h"

#include "qoscclient.h"
#include <QtNetwork/QHostAddress>

#include <QtGui/QtGui>

class Global
{
	Global() {}
	public:
		static Global* the() {
			static Global* me = new Global();
			return me;
		}

		QList<QVariant> ids;
};

BleepWidget::BleepWidget( QWidget* p )
	: QWidget( p, Qt::FramelessWindowHint )
{
	Global::the()->ids.push_back( me = Global::the()->ids.size()+1 );
	setMaximumSize( 150,150 );
	setAngle( 0 );

	QAction* actionnew = new QAction( "Add me a buddy!", this );
	connect( actionnew, SIGNAL( triggered() ), this, SLOT( newBleep() ) );
	addAction( actionnew );

	QAction* actiondel = new QAction( "Delete me, I am tired.", this );
	connect( actiondel, SIGNAL( triggered() ), this, SLOT( close() ) );
	addAction( actiondel );
}
BleepWidget::~BleepWidget() {
	qDebug( "BleepWidget::~BleepWidget()" );
}

void BleepWidget::setAngle( double a ) {
	//qDebug( "BleepWidget::setAngle( %e )", a );
	angle = a;
	sendData();
	update();
}

void BleepWidget::resizeEvent( QResizeEvent* ) {
	setAngle( angle );
}

void BleepWidget::paintEvent( QPaintEvent* ) {
	double h = qMin( width()*0.8, height()*0.8 );
	QPainterPath path;
	path.moveTo( -h/4, h/2-1 );
	path.lineTo( -h/4, 0 );
	path.lineTo( 0, -h/2 );
	path.lineTo( h/4, 0 );
	path.lineTo( h/4, h/2-1 );
	path.lineTo( -h/4, h/2-1 );

	QPainter p( this );
	p.setRenderHints( QPainter::Antialiasing );

	p.translate( width()/2, height()/2 );
	p.rotate( angle );

	//p.fillRect( QRectF( -h/4, -h/2, h/2, h ), QColor( 255,150,0 ) );

	p.setPen( Qt::NoPen );
	p.setBrush( QColor( 255,150,0 ) );

	p.drawPath( path );


	QBitmap bitmap( this->size() );
	bitmap.clear();
	QPainter p2( &bitmap );
	p2.translate( width()/2, height()/2 );
	p2.rotate( angle );
	p2.setBrush( QColor( 0,0,0 ) );
	p2.drawPath( path );

	if ( mask() != bitmap )
		setMask( bitmap );
}

void BleepWidget::mouseMoveEvent( QMouseEvent* ev ) {
	move( ev->globalPos() - QPoint( width()/2, height()/2 ) );
}

void BleepWidget::wheelEvent( QWheelEvent* ev ) {
	setAngle( angle + ev->delta()/10.0 );
}
void BleepWidget::mouseReleaseEvent( QMouseEvent* ev ) {
	if ( ev->button() == Qt::LeftButton )
		sendData();
	else
		ev->ignore();
}

void BleepWidget::moveEvent( QMoveEvent* ) {
	sendData();
}

void BleepWidget::sendData() {
	static QOscClient* client = new QOscClient( QHostAddress( QHostAddress::LocalHost ), 3333, 0 );
	client->sendData( "/tuio/2Dobj", QList<QVariant>() << "alive" << Global::the()->ids );
	client->sendData( "/tuio/2Dobj", QList<QVariant>() << "set" << me << me
		<< double( pos().x() ) /* x */
		<< double( pos().y() ) /* y */
		<< angle/180 /* angle */
		<< 0.0 /* x-move */
		<< 0.0 /* y-move */
		<< 0.0 /* angle-move */
		<< 0.0 /* accel */
		<< 0.0 /* rotation-accel */
	);
}

void BleepWidget::contextMenuEvent( QContextMenuEvent* ev ) {
	QMenu::exec( actions(), ev->globalPos() );
}

void BleepWidget::newBleep() {
	QWidget* tmp = new BleepWidget( 0 );
	tmp->show();
}

