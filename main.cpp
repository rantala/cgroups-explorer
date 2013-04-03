/*
 * Copyright (C) 2011 Tommi Rantala <tt.rantala@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.
 */

#include "CgroupStatisticsModel.h"
#include "CgroupTaskModel.h"
#include "CgroupInfo.h"
#include <MDeclarativeCache>
#include <QApplication>
#include <QtDeclarative>
#include <QtGlobal>
#include <QTranslator>

Q_DECL_EXPORT int main(int argc, char **argv)
{
	QApplication *app = MDeclarativeCache::qApplication(argc, argv);
	QDeclarativeView *window = MDeclarativeCache::qDeclarativeView();
	QTranslator translator;
	translator.load("cgroups-explorer_" + QLocale::system().name(),
			"/usr/share/l10n/meegotouch");
	app->installTranslator(&translator);
	app->setProperty("NoMStyle", true);
	qmlRegisterType<CgroupInfo>("rantala.cgroups", 1, 0, "CgroupInfo");
	qmlRegisterType<CgroupTaskModel>("rantala.cgroups", 1, 0, "CgroupTaskModel");
	qmlRegisterType<CgroupStatisticsModel>("rantala.cgroups", 1, 0, "CgroupStatisticsModel");
	window->setSource(QUrl("qrc:/qmldir/main.qml"));
	window->showFullScreen();
	return app->exec();
}
