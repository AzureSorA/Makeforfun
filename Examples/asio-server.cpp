#include<boost/asio.hpp>
#include<boost/bind.hpp>
using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::system::error_code;

io_service service;
size_t read_complete(char* buff, const error_code& err, size_t bytes) {
    if (err) return 0;
    bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
    // 我们一个一个读取直到读到回车，不缓存
    return found ? 0 : 1;
}

void handle_connections() {
    tcp::acceptor acceptor(service, tcp::endpoint(tcp::v4(), 8001));
    char buff[1024];
    while (true) {
        tcp::socket sock(service);
        acceptor.accept(sock);
        int bytes = boost::asio::read(sock, boost::asio::buffer(buff), boost::bind(read_complete, buff, _1, _2));
        std::string msg(buff, bytes);
        sock.write_some(boost::asio::buffer(msg));
        sock.close();
    }
}

int main(int argc, char* argv[]) {
    handle_connections();
}