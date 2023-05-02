/**************************************************************************
 *  MainWindow.cpp
 *  Created 31/03/2023 by Dimitar T. Dimitrov
 *  mitakatdd@gmail.com
 *
 *  BSD 2-Clause "Simplified" License
 *
 **************************************************************************/
#include "MainWindow.h"
#include "qsystemtrayicon.h"
#include <QtCore>
#include <QSettings>
#include <QDesktopServices>
#include <QtWidgets/QApplication>
#include <QMenu>
#include <QAction>
#include <QImage>
#include <QIcon>
#include <QMessageBox>
#include <QTimer>
#include <windows.h>
#include <QHotkey>

#include "ConfigWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	userSettings = new QSettings("autoclick_settings");
//	lastUpdate = userSettings->value("LastUpdate", QDateTime::currentDateTimeUtc()).toDateTime();
	currentHotkey = QKeySequence(userSettings->value("HotKey", "Alt+Shift+S").toString());
	qDebug() << "Hotkey is: " << currentHotkey.toString();

	trayIcon = new QSystemTrayIcon(QIcon(":/autoclick_icon.png"), this);
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(menuClicked(QSystemTrayIcon::ActivationReason)));
	trayIcon->show();
	trayIcon->setToolTip("Auto Clicker!");

	QAction *aboutAction = new QAction("About", trayIcon);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

	QAction *quitAction = new QAction(tr("Exit"), trayIcon );
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

	toggleAction = new QAction(tr("Toggle Right click"), trayIcon );
//	quitAction->setShortcut(QKeySequence("CTRL+SHIFT+X"));
	connect(toggleAction, SIGNAL(triggered()), this, SLOT(toggleRightClick()));

	mainMenu = new QMenu;
	mainMenu->addAction(aboutAction);
	mainMenu->addSeparator();
	mainMenu->addAction(toggleAction);
	mainMenu->addSeparator();
	mainMenu->addAction(quitAction);
	trayIcon->setContextMenu(mainMenu);

	hotkey = new QHotkey(this);
	hotkey->setShortcut(currentHotkey, true);
	connect(hotkey, &QHotkey::activated, this, [&](){ toggleClicker(); });

	configWidget = new ConfigWidget(hotkey);
	connect(configWidget, SIGNAL(hotkeyChanged(const QKeySequence)), this, SLOT(hotkeyChanged(const QKeySequence)));

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
}

MainWindow::~MainWindow()
{
	mainMenu->clear();

	delete configWidget;
	delete userSettings;
	delete trayIcon;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (event)
		QApplication::quit();
}

void MainWindow::menuClicked(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::ActivationReason::Trigger)
		configWidget->show();
}

void MainWindow::showAbout()
{
	QMessageBox::about(this, "About", tr("About info"));
}

void MainWindow::toggleClicker()
{
	isActive = !isActive;
	qDebug() << "Toggled to" << isActive;

	if (isActive) {
		timer->start(rightClick?1000:100);
	} else {
		timer->stop();
	}
}

void MainWindow::toggleRightClick()
{
	rightClick = !rightClick;

	if (rightClick)
	{
		toggleAction->setText("Toggle Left click");
	} else {
		toggleAction->setText("Toggle Right click");
	}
}

void MainWindow::SetNumLock(bool state)
{
   BYTE keyState[256];

   GetKeyboardState((LPBYTE)&keyState);
   if( (state && !(keyState[VK_NUMLOCK] & 1)) ||
	   (!state && (keyState[VK_NUMLOCK] & 1)) )
   {
   // Simulate a key press
	  keybd_event( VK_NUMLOCK,
				   0x45,
				   KEYEVENTF_EXTENDEDKEY | 0,
				   0 );

   // Simulate a key release
	  keybd_event( VK_NUMLOCK,
				   0x45,
				   KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
				   0);
   }
}


void MainWindow::updateTimer()
{
	if (rightClick) {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		QThread::msleep(500);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	} else {
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
}

void MainWindow::hotkeyChanged(const QKeySequence &keySequence)
{
	if (keySequence.isEmpty())
		return;

	currentHotkey = keySequence;
	qDebug() << " Hotkey changed to: " + keySequence.toString();
	hotkey->setShortcut(currentHotkey, true);
	userSettings->setValue("HotKey", currentHotkey.toString());
}
