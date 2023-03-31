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

	bool isActive = false;

	void closeEvent(QCloseEvent *event);

	ConfigWidget* configWidget;

	QHotkey *hotkey;

	QTimer *timer;

private slots:
	void menuClicked(QSystemTrayIcon::ActivationReason reason);
	void showAbout();
	void toggleClicker();
	void updateTimer();

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
};

#endif // MAINWINDOW_H
