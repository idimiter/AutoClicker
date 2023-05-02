#include "ConfigWidget.h"
#include <QHotkey>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QKeySequenceEdit>

ConfigWidget::ConfigWidget(QHotkey* hotkey, QWidget *parent) : QWidget{parent}
{
	this->hotkey = hotkey;

	resize(640, 480);
	QGridLayout *mainLayout = new QGridLayout(this);

	QLabel *titleLabel = new QLabel(QString("Shortcut"));
	titleLabel->setMargin(0);

	QKeySequenceEdit *hotkeyEdit = new QKeySequenceEdit(hotkey->shortcut());
	connect(hotkeyEdit, SIGNAL(keySequenceChanged(const QKeySequence)), this, SLOT(setHotkey(const QKeySequence)));

	mainLayout->addWidget(titleLabel, 0, 0);
	mainLayout->addWidget(hotkeyEdit, 0, 1);
}

void ConfigWidget::setHotkey(const QKeySequence &keySequence)
{
	emit hotkeyChanged(keySequence);
}
