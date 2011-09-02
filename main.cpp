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
