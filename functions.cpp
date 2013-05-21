//unit functions.cpp

#include <QtCore>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <time.h>
#if defined(Q_OS_UNIX)
#include <X11/Xlib.h>
#elif defined(Q_OS_WIN)
#include <windows.h>
#endif

#include "functions.h"

//var
CIniFile rIniFile;
//endvar

bool Graphic() {
#if defined(Q_OS_UNIX)
//var
    Display* pDisplay;
//endvar

    if ( (pDisplay = XOpenDisplay(getenv(QString2PChar("DISPLAY")))) == NULL )
        return false;
    else
#endif
        return true;
}

QString PChar2QString(const char* psPChar) {
    return QString("%1").arg(psPChar);
}

char* QString2PChar(const QString sString) {
    return sString.toAscii().data();
}

bool WriteToFile(const QString sDestFile, const QString sToFile, const bool fRewrite) {
//var
    QFile rFileStream(sDestFile);
    QTextStream* prTextStream;
//endvar

    if ( fRewrite ) {
        rFileStream.open(QIODevice::WriteOnly | QIODevice::Text);
    } else
        rFileStream.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    if ( rFileStream.isOpen() ) {
        prTextStream = new QTextStream(&rFileStream);
        prTextStream->operator << (sToFile);
        rFileStream.close();
        delete(prTextStream);
        return true;
    }
    return false;
}

void Sleep(const signed int nMilliSeconds)
{
#if defined(Q_OS_WIN)
    Sleep(nMilliSeconds);
#else
    usleep(nMilliSeconds);
#endif
}

QString CIniFile::Read(const QString sFileName, const QString sSection, const QString sValue,
                             const QString sDefault) {
//var
    QSettings Settings(m_sIniFile, QSettings::IniFormat);
//endvar

    m_sIniFile = sFileName;
    Settings.beginGroup(sSection);
    m_sResult = Settings.value(sValue, "").toString();
    if ( m_sResult == "" )
        m_sResult = sDefault;
    Settings.endGroup();
    return m_sResult;
}

void CIniFile::Save(const QString sFileName, const QString sSection, const QString sValue, const QString sInValue) {
//var
    QSettings Settings(m_sIniFile, QSettings::IniFormat);
//endvar

    m_sIniFile = sFileName;
    Settings.beginGroup(sSection);
    Settings.setValue(sValue, sInValue);
    Settings.endGroup();
}
