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
	configWidget = new ConfigWidget();

	userSettings = new QSettings("autoclick_settings");
//	lastUpdate = userSettings->value("LastUpdate", QDateTime::currentDateTimeUtc()).toDateTime();
//	qDebug() << "Last updated: " << timeAgo(lastUpdate);

	trayIcon = new QSystemTrayIcon(QIcon(":/autoclick_icon.png"), this);
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(menuClicked(QSystemTrayIcon::ActivationReason)));
	trayIcon->show();
	trayIcon->setToolTip("Auto Clicker!");

	QAction *aboutAction = new QAction("About", trayIcon);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

	QAction *quitAction = new QAction(tr("Exit"), trayIcon );
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

	toggleAction = new QAction(tr("Toggle ON"), trayIcon );
//	quitAction->setShortcut(QKeySequence("CTRL+SHIFT+X"));
	connect(toggleAction, SIGNAL(triggered()), this, SLOT(toggleClicker()));

	mainMenu = new QMenu;
	mainMenu->addAction(aboutAction);
	mainMenu->addSeparator();
	mainMenu->addAction(toggleAction);
	mainMenu->addSeparator();
	mainMenu->addAction(quitAction);
	trayIcon->setContextMenu(mainMenu);

	hotkey = new QHotkey(this);
	hotkey->setShortcut(QKeySequence("Alt+Shift+S"), true);
	connect(hotkey, &QHotkey::activated, this, [&](){ toggleClicker(); });

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
	qDebug() << "Toggled to " + QString::number(isActive);

	if (isActive) {
		timer->stop();
		toggleAction->setText("Toggle ON");
	} else {
		toggleAction->setText("Toggle OFF");
		timer->start(100);
	}

	isActive = !isActive;
}

void MainWindow::updateTimer()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
