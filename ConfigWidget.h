#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>

class QHotkey;
class QKeySequence;
class ConfigWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ConfigWidget(QHotkey* hotkey, QWidget *parent = nullptr);
private:
	QHotkey *hotkey;

private slots:
	void hotkeyChanged(const QKeySequence &keySequence);
};

#endif // CONFIGWIDGET_H
