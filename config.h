//unit config.h

#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

#include "main.h"

void ReadConfig();
bool SaveConfig();

struct g_CConfigVar {
    QString m_Main_sServer;
    QString m_Main_sExecutable;
    QString m_Main_sLanguage;
    QString m_Main_sAutostart;
    QString m_Main_sRestart;
    QString m_Main_sScriptGen;
    QString m_Main_sDisableConfigs;
    QString m_Main_sAdditionalCommands;
    QString m_Main_sForceIniEdit;

    QString m_HLDSConfig_sIP;
    QString m_HLDSConfig_sPort;
    QString m_HLDSConfig_sMaxPlayers;
    QString m_HLDSConfig_sGameConfigs;
    QString m_HLDSConfig_sConsole;
    QString m_HLDSConfig_sGame;
    QString m_HLDSConfig_sHostName;
    QString m_HLDSConfig_sMap;
    QString m_HLDSConfig_sAntiCheat;
    QString m_HLDSConfig_sMoTD;
    QString m_HLDSConfig_sInternetGame;
    QString m_HLDSConfig_sMasterServer;
    QString m_HLDSConfig_sTickRate;
    QString m_HLDSConfig_sFPS;

    QString m_COD4DSConfig_sIP;
    QString m_COD4DSConfig_sPort;
    QString m_COD4DSConfig_sMaxPlayers;
    QString m_COD4DSConfig_sGameConfigs;
    QString m_COD4DSConfig_sMapRotate;
    QString m_COD4DSConfig_sAntiCheat;

    QString m_STALKERDSConfig_sIP;
    QString m_STALKERDSConfig_sPort;
    QString m_STALKERDSConfig_sMaxPlayers;
    QString m_STALKERDSConfig_sGameConfigs;
    QString m_STALKERDSConfig_sGameType;
    QString m_STALKERDSConfig_sHostName;
    QString m_STALKERDSConfig_sMap;
    QString m_STALKERDSConfig_sButEnter;
    QString m_STALKERDSConfig_sInternetGame;
    QString m_STALKERDSConfig_sPassword;
    QString m_STALKERDSConfig_sGameConfigsPath;
    QString m_STALKERDSConfig_sSound;
};
extern g_CConfigVar g_rConfigVar;

#endif
