/**************************************************************************
 *  MainWindow.h
 *  Created 26/5/2016 by Dimitar T. Dimitrov
 *  mitakatdd@gmail.com
 *
 *  MIT License
 *
 **************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

class QDateTime;
class QMenu;
class QAction;
class QTimer;
class QSettings;
class ConfigWidget;
class QHotkey;

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	QSettings *userSettings;
	QSystemTrayIcon *trayIcon;
	QMenu *mainMenu;
	QAction *toggleAction;
	ConfigWidget* configWidget;
	QHotkey *hotkey;
	QTimer *timer;

	bool isActive = false;
	bool rightClick = false;

	void closeEvent(QCloseEvent *event);
	void SetNumLock(bool state);


private slots:
	void menuClicked(QSystemTrayIcon::ActivationReason reason);
	void showAbout();
	void toggleClicker();
	void toggleRightClick();
	void updateTimer();

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
};

#endif // MAINWINDOW_H
