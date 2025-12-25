#pragma once

#include <unistd.h>
#include <sys/socket.h>

class Socket
{
    public:
        explicit Socket(int fd = -1) noexcept : fd(fd) {}
        //Disallow copying,
        Socket(Socket const&) = delete;
        Socket& operator=(Socket const&) = delete;

        Socket(Socket&& other) noexcept : fd(other.fd){other.fd = -1;}

        Socket& operator=(Socket&& other) noexcept
        {
            if (this != &other)
            {
                close();
                fd = other.fd_;
                other.fd_ = -1;
            }
            return *this;
        }
        ~Socket() {close();}
        int fd() const { return fd; }
        bool valid() const noexcept { return fd != -1; }

    private:
        int fd;

        void close() noexcept {
            if (fd_ != -1)
            {
                ::close(fd);
                fd_ = -1;
            }
        }
};