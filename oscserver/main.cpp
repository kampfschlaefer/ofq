
#include "main.h"

#include "qoscserver.h"
#include <QtGui/QtGui>

MainWidget::MainWidget( QWidget* p ) : QWidget( p ) {
	setupUi( this );
}
MainWidget::~MainWidget() {
}
void MainWidget::on_buttonBox_clicked( QAbstractButton* button ) {
	if ( button->text() == "Reset" )
		reset();
}
void MainWidget::reset() {
	txtString->setText( "" );
	integerSpinBox->setValue( 0 );
	doubleSpinBox->setValue( 0.0 );
	spinbox2->setValue( 0 );
	spinbox3->setValue( 0 );
}

int main( int argc, char** argv )
{
	QApplication* app = new QApplication( argc, argv );

	QOscServer* server = new QOscServer( 5282, app );

	MainWidget* w = new MainWidget( 0 );
	w->show();

	PathObject* integerobj = new PathObject( "/int", QVariant::Int, server );
	QObject::connect( integerobj, SIGNAL( data( int ) ), w->integerSpinBox, SLOT( setValue( int ) ) );
	PathObject* doubleobj = new PathObject( "/double", QVariant::Double, server );
	QObject::connect( doubleobj, SIGNAL( data( double ) ), w->doubleSpinBox, SLOT( setValue( double ) ) );
	PathObject* stringobj = new PathObject( "/string", QVariant::String, server );
	QObject::connect( stringobj, SIGNAL( data( QString ) ), w->txtString, SLOT( setText( QString ) ) );
	/*PathObject* quit = new PathObject( "/quit", QVariant::Invalid, server );
	QObject::connect( quit, SIGNAL( data() ), w, SLOT( close() ) );*/

	int ret = app->exec();

	delete app;
	return ret;
};

