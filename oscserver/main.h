#ifndef MAIN_H
#define MAIN_H

#include <QtGui/QWidget>

#include "servergui_base.h"

class MainWidget : public QWidget, public Ui_ServerGui_Base
{
	Q_OBJECT
	public:
		MainWidget( QWidget* );
		~MainWidget();

	private slots:
		void on_buttonBox_clicked( QAbstractButton* );
		void reset();
};

#endif // MAIN_H

