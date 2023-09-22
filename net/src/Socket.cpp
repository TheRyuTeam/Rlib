#include <net/Socket.h>
#include "private/SocketImpl.h"
#include <cassert>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/poll.h>

RLIB_START

Socket::Socket()
    : _impl(new SocketImpl)
{
}

void Socket::bind(const SocketAddress& address)
{
    if (!_impl->valid()) {
        init(address.af(), SOCK_STREAM, 0);
    }

    std::errc err;
    _impl->bind(address, err);
    make_socket_error(err);
}

void Socket::listen(int backlog)
{
    assert(_impl->valid());
    std::errc err;
    _impl->listen(backlog, err);
    make_socket_error(err);
}

Socket Socket::accept(SocketAddress& address)
{
    assert(_impl->valid());
    std::errc err;
    auto impl = _impl->accept(address, err);
    make_socket_error(err);
    return Socket(impl);
}

void Socket::connect(const SocketAddress& address)
{
    if (!_impl->valid()) {
        init(address.af(), SOCK_STREAM, 0);
    }

    std::errc err;
    _impl->connect(address, err);
    make_socket_error(err);
}

int Socket::recv(char* buff, int maxLen, int flags)
{
    std::errc err;
    int rc = _impl->recv(buff, maxLen, err, flags);
    make_socket_error(err);
    return rc;
}

int Socket::send(const char* buff, int len, int flags)
{
    std::errc err;
    int rc = _impl->send(buff, len, err, flags);
    make_socket_error(err);
    return rc;
}

int Socket::cmp(const Socket& other) const
{
    return _impl->cmp(*other._impl);
}

Socket::Socket(const std::shared_ptr<SocketImpl>& impl)
    : _impl(impl)
{
}

void Socket::init(int domain, int type, int protocol)
{
    _impl->init(domain, type, protocol);
}

bool Socket::isValid() const noexcept
{
    return _impl->valid();
}

SocketAddress Socket::address() const
{
    sockaddr addr{};
    socklen_t len = sizeof(addr);
    int rc = ::getsockname(_impl->fd(), &addr, &len);
    make_socket_error(static_cast<std::errc>(rc));
    return SocketAddress((const char*)&addr, SocketAddress::DummySize{ len });
}

int Socket::poll(std::vector<SocketPollEvent>& events, std::chrono::milliseconds timeout)
{
    std::vector<pollfd> fds;
    for (auto& e : events) {
        auto fd = e.socket._impl->fd();
        auto it = fds.begin();
        while (it != fds.end() && it->fd != fd) {
            ++it;
        }
        if (it == fds.end()) {
            it = fds.insert(fds.end(), { fd, 0, 0 });
        }
        it->events |= (short)e.events;
        e.revents = SocketPollEvent::SPE_NONE;
    }
    
    int rc = ::poll(fds.data(), fds.size(), timeout.count());
    if (rc == -1) {
        make_socket_error(static_cast<std::errc>(SocketImpl::getError()));
    }

    for (std::size_t i = 0; i < fds.size(); ++i) {
        events[i].revents = (SocketPollEvent::Event)fds[i].revents;
    }

    return rc;
}

void make_socket_error(std::errc error)
{
    if (error == std::errc()) {
        return;
    }

    if (error == std::errc::address_family_not_supported) {
	    throw AddressFamilyNotSupportedError();
    } else if (error == std::errc::address_in_use) {
        throw AddressInUseError();
    } else if (error == std::errc::address_not_available) {
        throw AddressNotAvailableError();
    } else if (error == std::errc::already_connected) {
        throw AlreadyConnectedError();
    } else if (error == std::errc::argument_list_too_long) {
        throw ArgumentListTooLongError();
    } else if (error == std::errc::argument_out_of_domain) {
        throw ArgumentOutOfDomainError();
    } else if (error == std::errc::bad_address) {
        throw BadAddressError();
    } else if (error == std::errc::bad_file_descriptor) {
        throw BadFileDescriptorError();
    } else if (error == std::errc::bad_message) {
        throw BadMessageError();
    } else if (error == std::errc::broken_pipe) {
        throw BrokenPipeError();
    } else if (error == std::errc::connection_aborted) {
        throw ConnectionAbortedError();
    } else if (error == std::errc::connection_already_in_progress) {
        throw ConnectionAlreadyInProgressError();
    } else if (error == std::errc::connection_refused) {
        throw ConnectionRefusedError();
    } else if (error == std::errc::connection_reset) {
        throw ConnectionResetError();
    } else if (error == std::errc::cross_device_link) {
        throw CrossDeviceLinkError();
    } else if (error == std::errc::destination_address_required) {
        throw DestinationAddressRequiredError();
    } else if (error == std::errc::device_or_resource_busy) {
        throw DeviceOrResourceBusyError();
    } else if (error == std::errc::directory_not_empty) {
        throw DirectoryNotEmptyError();
    } else if (error == std::errc::executable_format_error) {
        throw ExecutableFormatErrorError();
    } else if (error == std::errc::file_exists) {
        throw FileExistsError();
    } else if (error == std::errc::file_too_large) {
        throw FileTooLargeError();
    } else if (error == std::errc::filename_too_long) {
        throw FilenameTooLongError();
    } else if (error == std::errc::function_not_supported) {
        throw FunctionNotSupportedError();
    } else if (error == std::errc::host_unreachable) {
        throw HostUnreachableError();
    } else if (error == std::errc::identifier_removed) {
        throw IdentifierRemovedError();
    } else if (error == std::errc::illegal_byte_sequence) {
        throw IllegalByteSequenceError();
    } else if (error == std::errc::inappropriate_io_control_operation) {
        throw InappropriateIoControlOperationError();
    } else if (error == std::errc::interrupted) {
        throw InterruptedError();
    } else if (error == std::errc::invalid_argument) {
        throw InvalidArgumentError();
    } else if (error == std::errc::invalid_seek) {
        throw InvalidSeekError();
    } else if (error == std::errc::io_error) {
        throw IoErrorError();
    } else if (error == std::errc::is_a_directory) {
        throw IsADirectoryError();
    } else if (error == std::errc::message_size) {
        throw MessageSizeError();
    } else if (error == std::errc::network_down) {
        throw NetworkDownError();
    } else if (error == std::errc::network_reset) {
        throw NetworkResetError();
    } else if (error == std::errc::network_unreachable) {
        throw NetworkUnreachableError();
    } else if (error == std::errc::no_buffer_space) {
        throw NoBufferSpaceError();
    } else if (error == std::errc::no_child_process) {
        throw NoChildProcessError();
    } else if (error == std::errc::no_link) {
        throw NoLinkError();
    } else if (error == std::errc::no_lock_available) {
        throw NoLockAvailableError();
    } else if (error == std::errc::no_message_available) {
        throw NoMessageAvailableError();
    } else if (error == std::errc::no_message) {
        throw NoMessageError();
    } else if (error == std::errc::no_protocol_option) {
        throw NoProtocolOptionError();
    } else if (error == std::errc::no_space_on_device) {
        throw NoSpaceOnDeviceError();
    } else if (error == std::errc::no_stream_resources) {
        throw NoStreamResourcesError();
    } else if (error == std::errc::no_such_device_or_address) {
        throw NoSuchDeviceOrAddressError();
    } else if (error == std::errc::no_such_device) {
        throw NoSuchDeviceError();
    } else if (error == std::errc::no_such_file_or_directory) {
        throw NoSuchFileOrDirectoryError();
    } else if (error == std::errc::no_such_process) {
        throw NoSuchProcessError();
    } else if (error == std::errc::not_a_directory) {
        throw NotADirectoryError();
    } else if (error == std::errc::not_a_socket) {
        throw NotASocketError();
    } else if (error == std::errc::not_a_stream) {
        throw NotAStreamError();
    } else if (error == std::errc::not_connected) {
        throw NotConnectedError();
    } else if (error == std::errc::not_enough_memory) {
        throw NotEnoughMemoryError();
    } else if (error == std::errc::not_supported) {
        throw NotSupportedError();
    } else if (error == std::errc::operation_canceled) {
        throw OperationCanceledError();
    } else if (error == std::errc::operation_in_progress) {
        throw OperationInProgressError();
    } else if (error == std::errc::operation_not_permitted) {
        throw OperationNotPermittedError();
    } else if (error == std::errc::operation_not_supported) {
        throw OperationNotSupportedError();
    } else if (error == std::errc::operation_would_block) {
        throw OperationWouldBlockError();
    } else if (error == std::errc::owner_dead) {
        throw OwnerDeadError();
    } else if (error == std::errc::permission_denied) {
        throw PermissionDeniedError();
    } else if (error == std::errc::protocol_error) {
        throw ProtocolErrorError();
    } else if (error == std::errc::protocol_not_supported) {
        throw ProtocolNotSupportedError();
    } else if (error == std::errc::read_only_file_system) {
        throw ReadOnlyFileSystemError();
    } else if (error == std::errc::resource_deadlock_would_occur) {
        throw ResourceDeadlockWouldOccurError();
    } else if (error == std::errc::resource_unavailable_try_again) {
        throw ResourceUnavailableTryAgainError();
    } else if (error == std::errc::result_out_of_range) {
        throw ResultOutOfRangeError();
    } else if (error == std::errc::state_not_recoverable) {
        throw StateNotRecoverableError();
    } else if (error == std::errc::stream_timeout) {
        throw StreamTimeoutError();
    } else if (error == std::errc::text_file_busy) {
        throw TextFileBusyError();
    } else if (error == std::errc::timed_out) {
        throw TimedOutError();
    } else if (error == std::errc::too_many_files_open_in_system) {
        throw TooManyFilesOpenInSystemError();
    } else if (error == std::errc::too_many_files_open) {
        throw TooManyFilesOpenError();
    } else if (error == std::errc::too_many_links) {
        throw TooManyLinksError();
    } else if (error == std::errc::too_many_symbolic_link_levels) {
        throw TooManySymbolicLinkLevelsError();
    } else if (error == std::errc::value_too_large) {
        throw ValueTooLargeError();
    } else if (error == std::errc::value_too_large) {
        throw ValueTooLargeError();
    } else if (error == std::errc::wrong_protocol_type) {
        throw WrongProtocolTypeError();
    }
}

RLIB_END
