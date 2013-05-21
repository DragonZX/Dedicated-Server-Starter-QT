//unit main.h

#ifndef MAIN_H
#define MAIN_H

#define Q_GRAPHIC
#include <QtCore>

void Autostart(const bool bAction);
void Server(const QString sServer);
bool ScriptCreate();

const QString gc_sLanguage = QLocale::system().name();
const QString gc_sProgTitle = "Dedicated Server starter";
extern QString g_sProgDir;
extern QString g_sProgName;
extern QString g_sConfigFile;
extern QString g_sParameters;

#endif
