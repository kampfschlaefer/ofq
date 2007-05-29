#include <QtGui/QtGui>

int main( int argc, char** argv )
{
  QApplication* app = new QApplication( argc, argv );

  QPushButton* btn = new QPushButton( "Quit", 0 );
  QObject::connect(
      btn, SIGNAL( clicked() ),
      btn, SLOT( close() )
      );
  btn->show();

  return app->exec();
}
