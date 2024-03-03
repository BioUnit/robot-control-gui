#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent)
    : QObject{parent}
{}

bool TcpSocket::TcpConnect(){
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "connecting...";

    socket->connectToHost("192.168.0.107", 1000);

    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
        return false;
    } else {
        return true;
    }
}

void TcpSocket::TcpDisconnect(){
    socket->disconnectFromHost();
    qDebug("Disconnected");
}

void TcpSocket::connected()
{
    qDebug() << "connected...";

    socket->write("Ready");
}

void TcpSocket::write(const char *data)
{
    if(socket == NULL){
        qDebug() << "Error: Socket wasn't created";
    } else {
        if(socket->state() == QAbstractSocket::SocketState::UnconnectedState){
            qDebug() << "Error: Write operation suppressed - no connection";
        } else {
            socket->write(data);
        }
    }
}

void TcpSocket::disconnected()
{
    qDebug() << "disconnected...";
}

void TcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void TcpSocket::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << socket->readAll();
}

bool TcpSocket::isConnected(){
    //qDebug() << "Error: " << socket->state();
    if(socket == NULL){
        return false;
    } else {
        if(socket->state() == QAbstractSocket::SocketState::ConnectedState){
            return true;
        } else {
            return false;
        }
    }
}
