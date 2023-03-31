#include "ConfigWidget.h"
#include <QHBoxLayout>
#include <QLabel>

ConfigWidget::ConfigWidget(QWidget *parent) : QWidget{parent}
{
	resize(640, 480);
	QHBoxLayout *mainLayout = new QHBoxLayout(this);

	QLabel *titleLabel = new QLabel(QString("Test"));
	titleLabel->setMargin(0);

	mainLayout->addWidget(titleLabel);
}
