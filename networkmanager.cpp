#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent), m_socket(new QTcpSocket(this))
{
    connect(m_socket, &QTcpSocket::connected, this, &NetworkManager::onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &NetworkManager::onReadyRead);
    connect(m_socket, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::errorOccurred), this, &NetworkManager::onErrorOccurred);
}

void NetworkManager::fetchData()
{
    m_socket->connectToHost("jsonplaceholder.typicode.com", 80);
}

void NetworkManager::onConnected()
{
    QByteArray request = "GET /users HTTP/1.0\r\nHost: jsonplaceholder.typicode.com\r\n\r\n";
    m_socket->write(request);
}

void NetworkManager::onReadyRead()
{
    m_buffer.append(m_socket->readAll());

    if (m_buffer.contains("\r\n\r\n"))
    {
        int jsonStartIndex = m_buffer.indexOf("\r\n\r\n") + 4;
        QByteArray jsonData = m_buffer.mid(jsonStartIndex);
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);

        if (doc.isArray()) {
            emit dataReady(doc.array());
        } else {
            emit errorOccurred("Invalid JSON data received.");
        }
        m_socket->disconnectFromHost();
    }
}

void NetworkManager::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    emit errorOccurred(m_socket->errorString());
}