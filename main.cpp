/*	Copyright (C) 2011 Sorokin Alexei <sor.alexei@hotbox.ru>

        This program is free software: you can redistribute it and/or modify
        it under the terms of the Apache License as published by
        the Apache Software Foundation, either version 2 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
        See the Apache License for more details.

        You should have received a copy of the Apache License along
        with this program.  If not, see <http://www.apache.org/licenses/>. */

#include <QtCore>
#include <QApplication>
#include <QDesktopServices>
#include <QMessageBox>
#include <iostream>

#include "main.h"
#include "config.h"
#include "functions.h"

//var
QString g_sProgDir;
QString g_sProgName;
QString g_sConfigFile;
QString g_sParameters;
//endvar

int main(int nParamCount, char* psParamStr[]) {
//var
    QCoreApplication* prApplication;
#if defined(Q_GRAPHIC)
    if ( Graphic() )
        prApplication = new QApplication(nParamCount, psParamStr);
    else
#endif
        prApplication = new QCoreApplication(nParamCount, psParamStr);
    int nTemp = 0;
    QString sTemp = "";
    char* psTemp = QString2PChar("");
    QTranslator rQtTranslator, rTranslator;
    QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    QFileInfo rProgPath(PChar2QString(psParamStr[0]));
#if defined(Q_OS_WIN)
    QSettings* prRegistry;
    QString sConfigFileName = rProgPath.baseName().replace(".exe", "") + ".ini";
#else
    QString sConfigFileName = rProgPath.baseName() + ".ini";
#endif
//endvar

#if defined(Q_OS_WIN)
    prRegistry = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\FileSystem",
                     QSettings::NativeFormat);
    prRegistry->setValue("NtfsDisable8dot3NameCreation", 0);
    delete(prRegistry);
#endif
    g_sProgName = rProgPath.baseName();
    g_sProgDir = rProgPath.absolutePath();
    g_sConfigFile = g_sProgDir + "/" + sConfigFileName;
    QDir::setCurrent(g_sProgDir);
    g_sProgDir = QDir::currentPath();
    rQtTranslator.load("qt_" + QLocale::system().name());
    rTranslator.load("dss_" + QLocale::system().name(), "lang");
    prApplication->installTranslator(&rQtTranslator);
    prApplication->installTranslator(&rTranslator);
    g_rConfigVar.m_Main_sLanguage = "en";
#if defined(Q_OS_WIN)
    prRegistry = new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Valve\\Steam", QSettings::NativeFormat);
    g_rConfigVar.m_Main_sLanguage = prRegistry->value("Language", "en").toString();
    delete(prRegistry);
#endif
    ReadConfig();
    rQtTranslator.load("qt_" + g_rConfigVar.m_Main_sLanguage);
    rTranslator.load("dss_" + g_rConfigVar.m_Main_sLanguage, "lang");
    if ( g_rConfigVar.m_Main_sAutostart.toLower() == "false" )
        Autostart(false);
    else if ( g_rConfigVar.m_Main_sAutostart.toLower() != "disable" )
        Autostart(true);

    if ( ! QFile::exists(g_sConfigFile) ) {
        if ( SaveConfig() )
            sTemp = QObject::tr("Please edit \"%1\" and restart the program.").arg(sConfigFileName);
        else
            sTemp = "An error occurred!";
#if defined(Q_GRAPHIC)
        if ( Graphic() ) {
            QMessageBox::information(0, gc_sProgTitle, sTemp);
            QDesktopServices::openUrl(g_sConfigFile);
        } else {
#endif
            std::cout << QString2PChar(sTemp + "\n");
            Sleep(3000);
            nTemp = system(QString2PChar("editor " + g_sConfigFile));
        }
        return 0;
    }
    if ( ! QFile::exists(QFileInfo(g_rConfigVar.m_Main_sExecutable).fileName()) ||
         g_rConfigVar.m_Main_sForceIniEdit.toLower() != "true" ) {
        sTemp = QObject::tr("Error: \'%1\' was not found.").arg(QFileInfo(g_rConfigVar.m_Main_sExecutable).fileName());
#if defined(Q_GRAPHIC)
        if ( Graphic() )
            QMessageBox::warning(0, gc_sProgTitle, sTemp);
        else
#endif
            std::cout << QString2PChar(sTemp + "\n");
        SaveConfig();
        return 1;
    }
    if ( nParamCount != 0 ) {
        for ( nTemp = 1; nTemp <= nParamCount ; nTemp++  )
            g_sParameters = g_sParameters + ' ' +psParamStr[nParamCount];
         g_sParameters = g_sParameters + ' ' + g_rConfigVar.m_Main_sAdditionalCommands;
    } else {
        g_sParameters = g_rConfigVar.m_Main_sAdditionalCommands;
    }
    if ( g_rConfigVar.m_Main_sServer.toLower() == "callofduty4" )
        Server("cod4");
    else if ( g_rConfigVar.m_Main_sServer.toLower() == "callofduty" )
        Server("cod4");
    else if ( g_rConfigVar.m_Main_sServer.toLower() == "s.t.a.l.k.e.r." )
        Server("stalker");
    else
        Server("half-life");
    if ( g_rConfigVar.m_Main_sScriptGen.toLower() == "true" )
        ScriptCreate();
    nTemp = QMessageBox::Yes;
    psTemp = QString2PChar("y");
    while ( nTemp == QMessageBox::Yes ) {
        if ( ! system(QString2PChar(g_rConfigVar.m_Main_sExecutable + " " + g_sParameters)) )
        {
            if ( g_rConfigVar.m_Main_sRestart.toLower() == "true" ) {
#if defined(Q_GRAPHIC)
                if ( Graphic() )
                    nTemp = QMessageBox::question(0, gc_sProgTitle, QObject::tr("Restart the server?"), QMessageBox::Yes,
                                      QMessageBox::No | QMessageBox::Default | QMessageBox::Escape);
                else {
#endif
                    std::cout << QString2PChar(QObject::tr("Restart the server?") + " [Y/N]: ");
                    std::cin >> psTemp;
                    if ( PChar2QString(psTemp).toLower() != "y" )
                        nTemp = QMessageBox::No;
                }
            } else if ( g_rConfigVar.m_Main_sRestart.toLower() == "force" )
                nTemp = QMessageBox::Yes;
            else
                nTemp = QMessageBox::No;
            Sleep(100);
        } else
#if defined(Q_GRAPHIC)
            if ( Graphic() )
                nTemp = QMessageBox::critical(0, gc_sProgTitle, QObject::tr("An error occurred!"));
            else {
#endif
                std::cout << QString2PChar(QObject::tr("An error occurred!") + "\n");
                nTemp = QMessageBox::No;
            }
    }
    if ( SaveConfig() )
        return 0;
    else
        return 1;
}

void Autostart(const bool bAction) {
//var
#if defined(Q_OS_WIN)
    QSettings* prRegistry;
#elif defined(Q_OS_LINUX) or defined(Q_OS_FREEBSD)
    QString sAutostartPath;
#endif
//endvar

#if defined(Q_OS_LINUX) or defined(Q_OS_FREEBSD)
    if ( PChar2QString(getenv("XDG_CONFIG_HOME")) == "" )
        sAutostartPath = PChar2QString(getenv("HOME")) + "/.config/autostart/DedicatedServerStarter.desktop";
    else
        sAutostartPath = PChar2QString(getenv("XDG_CONFIG_HOME")) + "/autostart/DedicatedServerStarter.desktop";
#endif
    if ( bAction == true ) {
#if defined(Q_OS_LINUX) or defined(Q_OS_FREEBSD)
        WriteToFile(sAutostartPath, QString("[Desktop Entry]\nVersion=1.0\nName=") + gc_sProgTitle + QString("\nExec=") +
          g_sProgDir + QString("/") + g_sProgName + QString("\nTerminal=false\nType=Application\nHidden=true"), true);
#elif defined(Q_OS_WIN)
        prRegistry = new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                         QSettings::NativeFormat);
        prRegistry->setValue("DedicatedServerStarter", g_sProgDir + "/" + g_sProgName);
        delete(prRegistry);
#endif
    } else {
#if defined(Q_OS_LINUX) or defined(Q_OS_FREEBSD)
        QFile(sAutostartPath).remove();
#elif defined(Q_OS_WIN)
        prRegistry = new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                         QSettings::NativeFormat);
        prRegistry->remove("DedicatedServerStarter");
        delete(prRegistry);
#endif
    }
}

void Server(const QString sServerType) {
//var
    QString sServerDirectory = QFileInfo(g_rConfigVar.m_Main_sExecutable).absolutePath();
//endvar

    if ( sServerType == "half-life" ) {
        if ( g_rConfigVar.m_HLDSConfig_sGame != "" &&
                    QFile::exists(sServerDirectory + "/" + g_rConfigVar.m_HLDSConfig_sGame + "/steam_appid.txt") )
                QFile::copy(sServerDirectory + "/" + g_rConfigVar.m_HLDSConfig_sGame + "/steam_appid.txt",
                            sServerDirectory + "/" +"steam_appid.txt");
        if ( g_rConfigVar.m_HLDSConfig_sConsole.toLower() == "true" )
            g_sParameters = g_sParameters + " -console";
        else
            g_sParameters = g_sParameters + " -noconsole";
        if ( g_rConfigVar.m_HLDSConfig_sGame != "" )
            g_sParameters = g_sParameters + " -game " + g_rConfigVar.m_HLDSConfig_sGame;
        if ( g_rConfigVar.m_HLDSConfig_sHostName != "" )
            g_sParameters = g_sParameters + " +hostname \"" + g_rConfigVar.m_HLDSConfig_sHostName + "\"";
        if ( g_rConfigVar.m_HLDSConfig_sMap != "" )
            g_sParameters = g_sParameters + " +map " + g_rConfigVar.m_HLDSConfig_sMap;
        if ( g_rConfigVar.m_HLDSConfig_sMoTD != "" )
            g_sParameters = g_sParameters + " +motdfile " + g_rConfigVar.m_HLDSConfig_sMoTD;
        if ( g_rConfigVar.m_HLDSConfig_sIP != "" )
            g_sParameters = g_sParameters + " +ip " + g_rConfigVar.m_HLDSConfig_sIP;
        if ( g_rConfigVar.m_HLDSConfig_sPort != "" )
            g_sParameters = g_sParameters + " +port 27015";
        else
            g_sParameters = g_sParameters + " +port " + g_rConfigVar.m_HLDSConfig_sPort;
        if ( g_rConfigVar.m_HLDSConfig_sMaxPlayers != "" )
            g_sParameters = g_sParameters + " +maxclients " + g_rConfigVar.m_HLDSConfig_sMaxPlayers;
        if ( g_rConfigVar.m_HLDSConfig_sGameConfigs != "" )
            g_sParameters = g_sParameters + " +exec " + g_rConfigVar.m_HLDSConfig_sGameConfigs.replace("#", " +exec ");
        if ( g_rConfigVar.m_HLDSConfig_sTickRate != "" )
            g_sParameters = g_sParameters + " -tickrate " + g_rConfigVar.m_HLDSConfig_sTickRate;
        if ( g_rConfigVar.m_HLDSConfig_sFPS != "" )
            g_sParameters = g_sParameters + " +fps_max " + g_rConfigVar.m_HLDSConfig_sFPS;
        if ( g_rConfigVar.m_HLDSConfig_sInternetGame.toLower() == "false" )
               g_sParameters = g_sParameters + " +sv_lan 1";
        else
            g_sParameters = g_sParameters + " +sv_lan 0";
        if ( g_rConfigVar.m_HLDSConfig_sAntiCheat.toLower() == "false" )
            g_sParameters = g_sParameters + " -insecure";
        else
            g_sParameters = g_sParameters + " -secure";
        if ( g_rConfigVar.m_HLDSConfig_sMasterServer.toLower() == "false" )
            g_sParameters = g_sParameters + " -nomaster";
        else
            g_sParameters = g_sParameters + " -master";
    } else if ( sServerType == "cod4" ) {
        g_sParameters = g_sParameters + " +set dedicated 2";
        if ( g_rConfigVar.m_COD4DSConfig_sMapRotate.toLower() == "true" )
            g_sParameters = g_sParameters + " +map_rotate";
        if ( g_rConfigVar.m_COD4DSConfig_sIP != "" )
            g_sParameters = g_sParameters + " +set net_ip " + g_rConfigVar.m_COD4DSConfig_sIP;
        if ( g_rConfigVar.m_COD4DSConfig_sPort != "" )
            g_sParameters = g_sParameters + " +set net_port " + g_rConfigVar.m_COD4DSConfig_sPort;
        if ( g_rConfigVar.m_COD4DSConfig_sAntiCheat.toLower() == "false" )
            g_sParameters = g_sParameters + " +set sv_punkbuster \"0\"";
        else
            g_sParameters = g_sParameters + " +set sv_punkbuster \"1\"";
        if ( g_rConfigVar.m_COD4DSConfig_sMaxPlayers != "" )
            g_sParameters = g_sParameters + " +set sv_maxclients " + g_rConfigVar.m_COD4DSConfig_sMaxPlayers;
    } else {
        if ( g_rConfigVar.m_STALKERDSConfig_sIP == "" )
            g_sParameters = g_sParameters + " +set net_ip localhost";
        else
            g_sParameters = g_sParameters + " +set net_ip " + g_rConfigVar.m_STALKERDSConfig_sIP;
        if ( g_rConfigVar.m_STALKERDSConfig_sSound != "true" )
            g_sParameters = "-nosound " + g_sParameters;
        if ( g_rConfigVar.m_Main_sRestart.toLower() != "false" )
            g_sParameters = g_sParameters + " -silent_error_mode";
        if ( g_rConfigVar.m_STALKERDSConfig_sButEnter.toLower() != "true" )
            g_sParameters = g_sParameters + " -i";
        if ( g_rConfigVar.m_STALKERDSConfig_sGameConfigs != "" )
              g_sParameters = g_sParameters + " +exec " + g_rConfigVar.m_STALKERDSConfig_sGameConfigs.replace("#", " -svcfg ");
        if ( g_rConfigVar.m_STALKERDSConfig_sGameConfigsPath != "" )
              g_sParameters = g_sParameters + " -overlaypath " + g_rConfigVar.m_STALKERDSConfig_sGameConfigsPath;
          g_sParameters = g_sParameters + " -start server(";
        if ( g_rConfigVar.m_STALKERDSConfig_sMap == "" )
              g_sParameters = g_sParameters + "testers_mp_agroprom";
        else
              g_sParameters = g_sParameters + g_rConfigVar.m_STALKERDSConfig_sMap;
        if ( g_rConfigVar.m_STALKERDSConfig_sGameType == "" )
              g_sParameters = g_sParameters + "\\deathmatch";
        else
              g_sParameters = g_sParameters + "\\" + g_rConfigVar.m_STALKERDSConfig_sGameType.toLower();
        if ( g_rConfigVar.m_STALKERDSConfig_sHostName != "" )
              g_sParameters = g_sParameters + "\\hname=\"" + g_rConfigVar.m_STALKERDSConfig_sHostName + "\"";
        if ( g_rConfigVar.m_STALKERDSConfig_sMaxPlayers != "" )
              g_sParameters = g_sParameters + "\\maxplayers=" + g_rConfigVar.m_STALKERDSConfig_sMaxPlayers;
        if ( g_rConfigVar.m_STALKERDSConfig_sPassword != "" )
              g_sParameters = g_sParameters + "\\pasw=\"" + g_rConfigVar.m_STALKERDSConfig_sPassword + "\"";
        if ( g_rConfigVar.m_STALKERDSConfig_sInternetGame.toLower() != "false" )
              g_sParameters = g_sParameters + "\\public=1";
        else
              g_sParameters = g_sParameters + "\\public=0";
        if ( g_rConfigVar.m_STALKERDSConfig_sPort != "" )
              g_sParameters = g_sParameters + "\\portsv=" + g_rConfigVar.m_STALKERDSConfig_sPort;
        g_sParameters = g_sParameters + ") client(" + g_rConfigVar.m_STALKERDSConfig_sIP + ')';
    }
}

bool ScriptCreate() {
//var
#if defined(Q_OS_WIN)
    QString sScriptFile = g_sProgDir + "/" + g_sProgName.replace(".exe", "") + ".bat";
#else
    QString sScriptFile = g_sProgDir + "/" + g_sProgName + ".sh";
#endif
//endvar

#if defined(Q_OS_WIN)
    if ( WriteToFile(sScriptFile, "@echo off\n\n:main\ncls\n", true) ) {
        if ( g_rConfigVar.m_Main_sRestart.toLower() == "false" )
            WriteToFile(sScriptFile, "start \"Dedicated Server\" /D \"" +
                        g_rConfigVar.m_Main_sExecutable + "\" " + g_sParameters + "\n", false);
        else
            WriteToFile(sScriptFile, "echo n | start /wait \"Dedicated Server\" \"" +
                        g_rConfigVar.m_Main_sExecutable + "\" " + g_sParameters + "\n", false);
        if ( g_rConfigVar.m_Main_sRestart.toLower() == "force" )
            WriteToFile(sScriptFile, "goto main\n", false);
        else if ( g_rConfigVar.m_Main_sRestart.toLower() == "true" ) {
            WriteToFile(sScriptFile, "set /p Restart=Restart server? [Y/N]: \n", false);
            WriteToFile(sScriptFile, "if /i \"{%Restart%}\"==\"{y}\" ( goto main )\n", false);
#else
    if ( WriteToFile(sScriptFile, "#!/bin/sh\n\n", true) ) {
        if ( g_rConfigVar.m_Main_sRestart.toLower() == "force" )
            WriteToFile(sScriptFile, "while true; do\n  ", false);
        else if ( g_rConfigVar.m_Main_sRestart.toLower() == "true" )
            WriteToFile(sScriptFile, "while [ \"${Restart}\" = \"Y\" ]; do\n  ", false);
        if ( g_sParameters != "" )
            WriteToFile(sScriptFile, "exec \"" + g_rConfigVar.m_Main_sExecutable + "\" " +
                    g_sParameters, false);
        else
            WriteToFile(sScriptFile, "exec \"" + g_rConfigVar.m_Main_sExecutable + "\"", false);
        if ( g_rConfigVar.m_Main_sRestart.toLower() == "false" )
            WriteToFile(sScriptFile, "&", false);
        WriteToFile(sScriptFile, ";\n", false);
        if ( g_rConfigVar.m_Main_sRestart.toLower() == "true" ) {
            WriteToFile(sScriptFile, "echo -n \"Restart server? [Y/N]: \";\n", false);
            WriteToFile(sScriptFile, "read Restart;\n", false);
        if ( g_rConfigVar.m_Main_sRestart.toLower() != "false" )
            WriteToFile(sScriptFile, "done;\n", false);
#endif
        }
        return true;
    }
    return false;
}
