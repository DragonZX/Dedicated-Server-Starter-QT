//unit functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QObject>

#include "main.h"

bool Graphic();
QString PChar2QString(const char* psPChar);
char* QString2PChar(const QString sString);
bool WriteToFile(const QString sDestFile, const QString sText, const bool fRewrite);
void Sleep(const signed int nMilliSeconds);

class CIniFile: QObject {
    Q_OBJECT

public:
    QString Read(const QString sFileName, const QString sSection, const QString sValue,
              const QString sDefault);
    void Save(const QString sFileName, const QString sSection, const QString sValue, const QString sInValue);

private:
    QString m_sResult;
    QString m_sIniFile;
};

extern CIniFile rIniFile;

#endif
