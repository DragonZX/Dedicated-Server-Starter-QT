//unit config.cpp

#include <QtCore>

#include "main.h"
#include "functions.h"
#include "config.h"

//var
g_CConfigVar g_rConfigVar;
//endvar

void ReadConfig() {
    g_rConfigVar.m_Main_sServer = rIniFile.Read(g_sConfigFile, "Main", "Server", "GoldSrc");
#if defined(Q_OS_WIN)
    g_rConfigVar.m_Main_sExecutable = rIniFile.Read(g_sConfigFile, "Main", "Executable", "srcds.exe");
#else
    g_rConfigVar.m_Main_sExecutable = rIniFile.Read(g_sConfigFile, "Main", "Executable", "run_srcds");
#endif
    g_rConfigVar.m_Main_sExecutable = QFileInfo(g_rConfigVar.m_Main_sExecutable).absoluteFilePath();
    g_rConfigVar.m_Main_sLanguage = rIniFile.Read(g_sConfigFile, "Main", "Language", g_rConfigVar.m_Main_sLanguage);
#if defined(Q_OS_LINUX) or defined(Q_OS_FREEBSD) or defined(Q_OS_WIN)
    g_rConfigVar.m_Main_sAutostart = rIniFile.Read(g_sConfigFile, "Main", "Autostart", "False");
#else
    g_rConfigVar.m_Main_sAutostart = "Disable";
#endif
    g_rConfigVar.m_Main_sRestart = rIniFile.Read(g_sConfigFile, "Main", "Restart", "True");
    g_rConfigVar.m_Main_sScriptGen = rIniFile.Read(g_sConfigFile, "Main", "ScriptGen", "False");
    g_rConfigVar.m_Main_sDisableConfigs = rIniFile.Read(g_sConfigFile, "Main", "DisableConfigs", "False");
    g_rConfigVar.m_Main_sAdditionalCommands = rIniFile.Read(g_sConfigFile, "Main", "AdditionalCommands", "");
    g_rConfigVar.m_Main_sForceIniEdit = rIniFile.Read(g_sConfigFile, "Main", "ForceIniEdit", "False");

    g_rConfigVar.m_HLDSConfig_sIP = rIniFile.Read(g_sConfigFile, "HLDSConfig", "IP", "");
    g_rConfigVar.m_HLDSConfig_sPort = rIniFile.Read(g_sConfigFile, "HLDSConfig", "Port", "27015");
    g_rConfigVar.m_HLDSConfig_sMaxPlayers = rIniFile.Read(g_sConfigFile, "HLDSConfig", "MaxPlayers", "22");
    g_rConfigVar.m_HLDSConfig_sGameConfigs = rIniFile.Read(g_sConfigFile, "HLDSConfig", "GameConfigs", "server.cfg#mani_server.cfg");
    g_rConfigVar.m_HLDSConfig_sConsole = rIniFile.Read(g_sConfigFile, "HLDSConfig", "Console", "True");
    g_rConfigVar.m_HLDSConfig_sGame = rIniFile.Read(g_sConfigFile, "HLDSConfig", "Game", "cstrike");
    g_rConfigVar.m_HLDSConfig_sHostName = rIniFile.Read(g_sConfigFile, "HLDSConfig", "HostName", "");
    g_rConfigVar.m_HLDSConfig_sMap = rIniFile.Read(g_sConfigFile, "HLDSConfig", "Map", "de_dust2");
    g_rConfigVar.m_HLDSConfig_sAntiCheat = rIniFile.Read(g_sConfigFile, "HLDSConfig", "AntiCheat", "True");
    g_rConfigVar.m_HLDSConfig_sMoTD = rIniFile.Read(g_sConfigFile, "HLDSConfig", "MoTD", "motd.txt");
    g_rConfigVar.m_HLDSConfig_sInternetGame = rIniFile.Read(g_sConfigFile, "HLDSConfig", "InternetGame", "True");
    g_rConfigVar.m_HLDSConfig_sMasterServer = rIniFile.Read(g_sConfigFile, "HLDSConfig", "MasterServer", "True");
    g_rConfigVar.m_HLDSConfig_sTickRate = rIniFile.Read(g_sConfigFile, "HLDSConfig", "TickRate", "100");
    g_rConfigVar.m_HLDSConfig_sFPS = rIniFile.Read(g_sConfigFile, "HLDSConfig", "FPS", "1000");

    g_rConfigVar.m_COD4DSConfig_sIP = rIniFile.Read(g_sConfigFile, "COD4DSConfig", "IP", "");
    g_rConfigVar.m_COD4DSConfig_sPort = rIniFile.Read(g_sConfigFile, "COD4DSConfig", "Port", "28961");
    g_rConfigVar.m_COD4DSConfig_sMaxPlayers = rIniFile.Read(g_sConfigFile, "COD4DSConfig", "MaxPlayers", "22");
    g_rConfigVar.m_COD4DSConfig_sGameConfigs = rIniFile.Read(g_sConfigFile, "COD4DSConfig", "GameConfigs", "");
    g_rConfigVar.m_COD4DSConfig_sMapRotate = rIniFile.Read(g_sConfigFile, "COD4DSConfig", "MapRotate", "True");
    g_rConfigVar.m_COD4DSConfig_sAntiCheat = rIniFile.Read(g_sConfigFile, "COD4DSConfig", "AntiCheat", "True");

    g_rConfigVar.m_STALKERDSConfig_sIP = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "IP", "");
    g_rConfigVar.m_STALKERDSConfig_sPort = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "Port", "5445");
    g_rConfigVar.m_STALKERDSConfig_sMaxPlayers = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "MaxPlayers", "22");
    g_rConfigVar.m_STALKERDSConfig_sGameConfigs = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "GameConfigs", "");
    g_rConfigVar.m_STALKERDSConfig_sGameType = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "GameType", "Deathmatch");
    g_rConfigVar.m_STALKERDSConfig_sHostName = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "HostName", "");
    g_rConfigVar.m_STALKERDSConfig_sMap = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "Map", "testers_mp_agroprom");
    g_rConfigVar.m_STALKERDSConfig_sButEnter = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "ButEnter", "False");
    g_rConfigVar.m_STALKERDSConfig_sInternetGame = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "InternetGame", "True");
    g_rConfigVar.m_STALKERDSConfig_sPassword = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "Password", "");
    g_rConfigVar.m_STALKERDSConfig_sGameConfigsPath = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "GameConfigsPath", "");
    g_rConfigVar.m_STALKERDSConfig_sSound = rIniFile.Read(g_sConfigFile, "STALKERDSConfig", "Sound", "False");
}

bool SaveConfig() {
    if ( ! WriteToFile(g_sConfigFile, "[Main]\n", true) )
        return false;
    WriteToFile(g_sConfigFile, "{" + QObject::tr("Main settings") + "}\n\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server mode (GoldSrc/Source, CallOfDuty4, STALKER)\n"), false);
    WriteToFile(g_sConfigFile, "Server=" + g_rConfigVar.m_Main_sServer + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Application to run (possible full path)\n"), false);
    WriteToFile(g_sConfigFile, "Executable=" + g_rConfigVar.m_Main_sExecutable + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Application language (by default: en)\n"), false);
    WriteToFile(g_sConfigFile, "Language=" + g_rConfigVar.m_Main_sLanguage + "\n", false);
#if defined(Q_OS_LINUX) or defined(Q_OS_FREEBSD) or defined(Q_OS_WIN)
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Add server to system autostart\n"), false);
    WriteToFile(g_sConfigFile, "Autostart=" + g_rConfigVar.m_Main_sAutostart + "\n", false);
#endif
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Restart server (True, Force, False)\n"), false);
    WriteToFile(g_sConfigFile, "Restart=" + g_rConfigVar.m_Main_sRestart + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Create Script-file before run\n"), false);
    WriteToFile(g_sConfigFile, "ScriptGen=" + g_rConfigVar.m_Main_sScriptGen + "\n", false);
    if ( g_rConfigVar.m_Main_sForceIniEdit.toLower() == "true" ) {
        WriteToFile(g_sConfigFile, "# " + QObject::tr("Force config editing\n"), false);
        WriteToFile(g_sConfigFile, "ForceIniEdit=" + g_rConfigVar.m_Main_sForceIniEdit + "\n", false);
    }
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Disable all commands, except the additional\n"), false);
    WriteToFile(g_sConfigFile, "DisableConfigs=" + g_rConfigVar.m_Main_sDisableConfigs + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Additional commands\n"), false);
    WriteToFile(g_sConfigFile, "AdditionalCommands=" + g_rConfigVar.m_Main_sAdditionalCommands + "\n", false);

    WriteToFile(g_sConfigFile, "\n[HLDSConfig]\n", false);
    WriteToFile(g_sConfigFile, "{" + QObject::tr("Specific only to GoldSrc/Source settings") + "}\n\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server IP\n"), false);
    WriteToFile(g_sConfigFile, "IP=" + g_rConfigVar.m_HLDSConfig_sIP + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server port (by default: 27015)\n"), false);
    WriteToFile(g_sConfigFile, "Port=" + g_rConfigVar.m_HLDSConfig_sPort + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Maximum number of players\n"), false);
    WriteToFile(g_sConfigFile, "MaxPlayers=" + g_rConfigVar.m_HLDSConfig_sMaxPlayers + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Plug-game configuration files (separated by lattice mark (#)\n"), false);
    WriteToFile(g_sConfigFile, "GameConfigs=" + g_rConfigVar.m_HLDSConfig_sGameConfigs + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Run the server in console mode\n"), false);
    WriteToFile(g_sConfigFile, "Console=" + g_rConfigVar.m_HLDSConfig_sConsole + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Catalog of the game, for which the server is created\n"), false);
    WriteToFile(g_sConfigFile, "Game=" + g_rConfigVar.m_HLDSConfig_sGame + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server name\n"), false);
    WriteToFile(g_sConfigFile, "HostName=" + g_rConfigVar.m_HLDSConfig_sHostName + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Game map\n"), false);
    WriteToFile(g_sConfigFile, "Map=" + g_rConfigVar.m_HLDSConfig_sMap + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Anti-Cheat Protection\n"), false);
    WriteToFile(g_sConfigFile, "AntiCheat=" + g_rConfigVar.m_HLDSConfig_sAntiCheat + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Image to be displayed upon entering the server\n"), false);
    WriteToFile(g_sConfigFile, "MoTD=" + g_rConfigVar.m_HLDSConfig_sMoTD + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Access to the server from the Internet\n"), false);
    WriteToFile(g_sConfigFile, "InternetGame=" + g_rConfigVar.m_HLDSConfig_sInternetGame + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("MasterServer usage\n"), false);
    WriteToFile(g_sConfigFile, "MasterServer=" + g_rConfigVar.m_HLDSConfig_sMasterServer + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Tickrate (33, 66, 100)\n"), false);
    WriteToFile(g_sConfigFile, "TickRate=" + g_rConfigVar.m_HLDSConfig_sTickRate + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server FPS (300, 600, 1000)\n"), false);
    WriteToFile(g_sConfigFile, "FPS=" + g_rConfigVar.m_HLDSConfig_sFPS + "\n", false);

    WriteToFile(g_sConfigFile, "\n[COD4DSConfig]\n", false);
    WriteToFile(g_sConfigFile, "{" + QObject::tr("Specific only to CallOfDuty4 settings") + "}\n\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server IP\n"), false);
    WriteToFile(g_sConfigFile, "IP=" + g_rConfigVar.m_COD4DSConfig_sIP + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server port (by default: 27015)\n"), false);
    WriteToFile(g_sConfigFile, "Port=" + g_rConfigVar.m_COD4DSConfig_sPort + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Maximum number of players\n"), false);
    WriteToFile(g_sConfigFile, "MaxPlayers=" + g_rConfigVar.m_COD4DSConfig_sMaxPlayers + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Plug-game configuration files (separated by lattice mark (#)\n"), false);
    WriteToFile(g_sConfigFile, "GameConfigs=" + g_rConfigVar.m_COD4DSConfig_sGameConfigs + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Map rotate\n"), false);
    WriteToFile(g_sConfigFile, "MapRotate=" + g_rConfigVar.m_COD4DSConfig_sMapRotate + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Anti-Cheat Protection\n"), false);
    WriteToFile(g_sConfigFile, "AntiCheat=" + g_rConfigVar.m_COD4DSConfig_sAntiCheat + "\n", false);

    WriteToFile(g_sConfigFile, "\n[STALKERDSConfig]\n", false);
    WriteToFile(g_sConfigFile, "{" + QObject::tr("Specific only to STALKER settings") + "}\n\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server IP\n"), false);
    WriteToFile(g_sConfigFile, "IP=" + g_rConfigVar.m_STALKERDSConfig_sIP + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server port (by default: 27015)\n"), false);
    WriteToFile(g_sConfigFile, "Port=" + g_rConfigVar.m_STALKERDSConfig_sPort + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Maximum number of players\n"), false);
    WriteToFile(g_sConfigFile, "MaxPlayers=" + g_rConfigVar.m_STALKERDSConfig_sMaxPlayers + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Plug-game configuration files (separated by lattice mark (#)\n"), false);
    WriteToFile(g_sConfigFile, "GameConfigs=" + g_rConfigVar.m_STALKERDSConfig_sGameConfigs + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Game type (Deathmatch, TeamDeathmatch, ArtefactHunt)\n"), false);
    WriteToFile(g_sConfigFile, "GameType=" + g_rConfigVar.m_STALKERDSConfig_sGameType + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server name\n"), false);
    WriteToFile(g_sConfigFile, "HostName=" + g_rConfigVar.m_STALKERDSConfig_sHostName + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Game map\n"), false);
    WriteToFile(g_sConfigFile, "Map=" + g_rConfigVar.m_STALKERDSConfig_sMap + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Capture input\n"), false);
    WriteToFile(g_sConfigFile, "ButEnter=" + g_rConfigVar.m_STALKERDSConfig_sButEnter + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Access to the server from the Internet\n"), false);
    WriteToFile(g_sConfigFile, "InternetGame=" + g_rConfigVar.m_STALKERDSConfig_sInternetGame + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Server password\n"), false);
    WriteToFile(g_sConfigFile, "Password=" + g_rConfigVar.m_STALKERDSConfig_sPassword + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Path to configuration file\n"), false);
    WriteToFile(g_sConfigFile, "GameConfigsPath=" + g_rConfigVar.m_STALKERDSConfig_sGameConfigsPath + "\n", false);
    WriteToFile(g_sConfigFile, "# " + QObject::tr("Play sounds on server\n"), false);
    WriteToFile(g_sConfigFile, "Sound=" + g_rConfigVar.m_STALKERDSConfig_sSound + "\n", false);
    return true;
}
