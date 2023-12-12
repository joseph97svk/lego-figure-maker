//
// Created by josephvalverde on 12/11/23.
//

#include <expected>

export module TcpSocket;

import <memory>;
import <span>;

import SSLController;

export class TcpSocket {
  int socketId;
  int port;
  bool ipv6;
  bool ssl;

  std::unique_ptr<SSLController> sslController;

  const unsigned int BUFFER_SIZE = 512;
public:
    explicit TcpSocket(int port, bool ipv6);
    TcpSocket(int port, const std::string& certFileName, const std::string& keyFileName, bool ipv6);
    explicit TcpSocket(int socketFd);

    TcpSocket(TcpSocket&&) = delete;
    TcpSocket(const TcpSocket&) = delete;
    TcpSocket& operator=(TcpSocket&&) = delete;
    TcpSocket& operator=(const TcpSocket&) = delete;

    void connect(const std::string& host, int targetPort);
    void connect(const std::string& host, const std::string& service) const;

    void close() const;

    template<typename readDatatype>
    TcpSocket& operator>>(readDatatype& data);

    template<typename writeDatatype>
    TcpSocket& operator<<(const writeDatatype& data);

    void bind(int portToBindTo) const;
    void listen(int queueSize) const;

    [[nodiscard]] std::shared_ptr<TcpSocket> accept() const;
    [[nodiscard]] bool isSSL();

private:
    void setSocket();

    void ipv4Connect(const std::string& host, int port) const;
    void ipv6Connect(const std::string& host, int port) const;

    void Write(const std::span<char>& message) const;
    [[nodiscard]] std::pair<std::vector<char>, unsigned int> Read() const;
};