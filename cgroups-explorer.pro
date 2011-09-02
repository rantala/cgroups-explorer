TEMPLATE = app
DEPENDPATH += .
HEADERS += *.h
SOURCES += *.cpp
RESOURCES += qmlfiles.qrc
QT += declarative

target.path = /usr/bin
desktop.path = /usr/share/applications
desktop.files = cgroups-explorer.desktop
icon.path = /usr/share/icons
icon.files = cgroups-explorer.svg

TRANSLATIONS += \
	cgroups-explorer_fi.ts

qm.path = /usr/share/l10n/meegotouch
qm.files = cgroups-explorer_*.qm

INSTALLS += target desktop icon qm
#DEFINES += QT_NO_DEBUG_OUTPUT
CONFIG += debug
CONFIG += qdeclarative-boostable
