#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QNetworkInterface>

QString getMacAddress()
{
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!  netInterface.flags().testFlag(QNetworkInterface::IsLoopBack)
            && netInterface.flags().testFlag(QNetworkInterface::IsUp)
            && netInterface.flags().testFlag(QNetworkInterface::IsRunning)
        )
        {
            QString ans = netInterface.hardwareAddress();
            return ans.replace(":", "");
        }
    }
    return QString();
}

QString getUsername()
{
#ifdef Q_OS_WIN
    return getenv("USERNAME");
#else
    return getenv("USER");
#endif
}

#endif // UTIL_H
