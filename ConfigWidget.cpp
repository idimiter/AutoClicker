#include "ConfigWidget.h"
#include <QHBoxLayout>
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
	QHBoxLayout *mainLayout = new QHBoxLayout(this);

	QLabel *titleLabel = new QLabel(QString("Shortcut"));
	titleLabel->setMargin(0);

	QKeySequenceEdit *hotkeyEdit = new QKeySequenceEdit();
	connect(hotkeyEdit, SIGNAL(keySequenceChanged(const QKeySequence)), this, SLOT(hotkeyChanged(const QKeySequence)));

	QSpacerItem *spacer = new QSpacerItem(150, 10, QSizePolicy::Expanding);

	mainLayout->addWidget(titleLabel);
	mainLayout->addWidget(hotkeyEdit);
	mainLayout->addSpacerItem(spacer);
}

void ConfigWidget::hotkeyChanged(const QKeySequence &keySequence)
{
	if (keySequence.isEmpty())
		return;

	qDebug() << " Hotkey changed to: " + keySequence.toString();
	hotkey->setShortcut(keySequence, true);
}
