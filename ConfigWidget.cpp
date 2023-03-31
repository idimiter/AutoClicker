#include "ConfigWidget.h"
#include <QHBoxLayout>
#include <QLabel>

ConfigWidget::ConfigWidget(QWidget *parent) : QWidget{parent}
{
	QHBoxLayout *mainLayout = new QHBoxLayout(this);

	QLabel *titleLabel = new QLabel(QString("Test"));
	titleLabel->setMargin(0);

	mainLayout->addWidget(titleLabel);
}
