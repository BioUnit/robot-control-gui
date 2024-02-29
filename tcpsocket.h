#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class TcpSocket : public QObject
{
    Q_OBJECT
    QTcpSocket *socket = NULL;
public:
    explicit TcpSocket(QObject *parent = nullptr);
    bool TcpConnect();
    void TcpDisconnect();
    void write(const char *data);
    bool isConnected();

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
};

#endif // TCPSOCKET_H
