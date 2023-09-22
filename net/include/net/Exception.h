#pragma once
#include <foundation/Exception.h>

RLIB_START

class SocketError
    : public Exception
{
public:
    SocketError(const char* msg, std::errc code)
        : Exception(msg)
        , _code(code)
    {
    }

    SocketError(const std::string& msg, std::errc code)
        : Exception(msg)
        , _code(code)
    {
    }
    
    SocketError(std::string&& msg, std::errc code)
        : Exception(std::move(msg))
        , _code(code)
    {
    }

    SocketError(std::errc code)
        : Exception(std::make_error_code(code).message())
        , _code(code)
    {
    }

    std::errc code() const noexcept
    {
        return _code;
    }

    std::string msgWithCode() const
    {
        return msg() + ". Error code: " + std::to_string((long long int)_code);
    }

private:
    std::errc _code;
};

#define PP_NET_ERROR(Name, Code)\
class Name\
    : public SocketError\
{\
public:\
    Name(const char* msg)\
        : SocketError(msg, Code)\
    {\
    }\
\
    Name(const std::string& msg)\
        : SocketError(msg, Code)\
    {\
    }\
\
    Name(std::string&& msg)\
        : SocketError(std::move(msg), Code)\
    {\
    }\
\
    Name()\
        : SocketError(Code)\
    {\
    }\
}

PP_NET_ERROR(AddressFamilyNotSupportedError, std::errc::address_family_not_supported);
PP_NET_ERROR(AddressInUseError, std::errc::address_in_use);
PP_NET_ERROR(AddressNotAvailableError, std::errc::address_not_available);
PP_NET_ERROR(AlreadyConnectedError, std::errc::already_connected);
PP_NET_ERROR(ArgumentListTooLongError, std::errc::argument_list_too_long);
PP_NET_ERROR(ArgumentOutOfDomainError, std::errc::argument_out_of_domain);
PP_NET_ERROR(BadAddressError, std::errc::bad_address);
PP_NET_ERROR(BadFileDescriptorError, std::errc::bad_file_descriptor);
#ifdef EBADMSG
PP_NET_ERROR(BadMessageError, std::errc::bad_message);
#endif
PP_NET_ERROR(BrokenPipeError, std::errc::broken_pipe);
PP_NET_ERROR(ConnectionAbortedError, std::errc::connection_aborted);
PP_NET_ERROR(ConnectionAlreadyInProgressError, std::errc::connection_already_in_progress);
PP_NET_ERROR(ConnectionRefusedError, std::errc::connection_refused);
PP_NET_ERROR(ConnectionResetError, std::errc::connection_reset);
PP_NET_ERROR(CrossDeviceLinkError, std::errc::cross_device_link);
PP_NET_ERROR(DestinationAddressRequiredError, std::errc::destination_address_required);
PP_NET_ERROR(DeviceOrResourceBusyError, std::errc::device_or_resource_busy);
PP_NET_ERROR(DirectoryNotEmptyError, std::errc::directory_not_empty);
PP_NET_ERROR(ExecutableFormatErrorError, std::errc::executable_format_error);
PP_NET_ERROR(FileExistsError, std::errc::file_exists);
PP_NET_ERROR(FileTooLargeError, std::errc::file_too_large);
PP_NET_ERROR(FilenameTooLongError, std::errc::filename_too_long);
PP_NET_ERROR(FunctionNotSupportedError, std::errc::function_not_supported);
PP_NET_ERROR(HostUnreachableError, std::errc::host_unreachable);
#ifdef EIDRM
PP_NET_ERROR(IdentifierRemovedError, std::errc::identifier_removed);
#endif
PP_NET_ERROR(IllegalByteSequenceError, std::errc::illegal_byte_sequence);
PP_NET_ERROR(InappropriateIoControlOperationError, std::errc::inappropriate_io_control_operation);
PP_NET_ERROR(InterruptedError, std::errc::interrupted);
PP_NET_ERROR(InvalidArgumentError, std::errc::invalid_argument);
PP_NET_ERROR(InvalidSeekError, std::errc::invalid_seek);
PP_NET_ERROR(IoErrorError, std::errc::io_error);
PP_NET_ERROR(IsADirectoryError, std::errc::is_a_directory);
PP_NET_ERROR(MessageSizeError, std::errc::message_size);
PP_NET_ERROR(NetworkDownError, std::errc::network_down);
PP_NET_ERROR(NetworkResetError, std::errc::network_reset);
PP_NET_ERROR(NetworkUnreachableError, std::errc::network_unreachable);
PP_NET_ERROR(NoBufferSpaceError, std::errc::no_buffer_space);
PP_NET_ERROR(NoChildProcessError, std::errc::no_child_process);
#ifdef ENOLINK
PP_NET_ERROR(NoLinkError, std::errc::no_link);
#endif
PP_NET_ERROR(NoLockAvailableError, std::errc::no_lock_available);
#ifdef ENODATA
PP_NET_ERROR(NoMessageAvailableError, std::errc::no_message_available);
#endif
PP_NET_ERROR(NoMessageError, std::errc::no_message);
PP_NET_ERROR(NoProtocolOptionError, std::errc::no_protocol_option);
PP_NET_ERROR(NoSpaceOnDeviceError, std::errc::no_space_on_device);
#ifdef ENOSR
PP_NET_ERROR(NoStreamResourcesError, std::errc::no_stream_resources);
#endif
PP_NET_ERROR(NoSuchDeviceOrAddressError, std::errc::no_such_device_or_address);
PP_NET_ERROR(NoSuchDeviceError, std::errc::no_such_device);
PP_NET_ERROR(NoSuchFileOrDirectoryError, std::errc::no_such_file_or_directory);
PP_NET_ERROR(NoSuchProcessError, std::errc::no_such_process);
PP_NET_ERROR(NotADirectoryError, std::errc::not_a_directory);
PP_NET_ERROR(NotASocketError, std::errc::not_a_socket);
#ifdef ENOSTR
PP_NET_ERROR(NotAStreamError, std::errc::not_a_stream);
#endif
PP_NET_ERROR(NotConnectedError, std::errc::not_connected);
PP_NET_ERROR(NotEnoughMemoryError, std::errc::not_enough_memory);
#ifdef ENOTSUP
PP_NET_ERROR(NotSupportedError, std::errc::not_supported);
#endif
#ifdef ECANCELED
PP_NET_ERROR(OperationCanceledError, std::errc::operation_canceled);
#endif
PP_NET_ERROR(OperationInProgressError, std::errc::operation_in_progress);
PP_NET_ERROR(OperationNotPermittedError, std::errc::operation_not_permitted);
PP_NET_ERROR(OperationNotSupportedError, std::errc::operation_not_supported);
PP_NET_ERROR(OperationWouldBlockError, std::errc::operation_would_block);
#ifdef EOWNERDEAD
PP_NET_ERROR(OwnerDeadError, std::errc::owner_dead);
#endif
PP_NET_ERROR(PermissionDeniedError, std::errc::permission_denied);
#ifdef EPROTO
PP_NET_ERROR(ProtocolErrorError, std::errc::protocol_error);
#endif
PP_NET_ERROR(ProtocolNotSupportedError, std::errc::protocol_not_supported);
PP_NET_ERROR(ReadOnlyFileSystemError, std::errc::read_only_file_system);
PP_NET_ERROR(ResourceDeadlockWouldOccurError, std::errc::resource_deadlock_would_occur);
PP_NET_ERROR(ResourceUnavailableTryAgainError, std::errc::resource_unavailable_try_again);
PP_NET_ERROR(ResultOutOfRangeError, std::errc::result_out_of_range);
#ifdef ENOTRECOVERABLE
PP_NET_ERROR(StateNotRecoverableError, std::errc::state_not_recoverable);
#endif
#ifdef ETIME
PP_NET_ERROR(StreamTimeoutError, std::errc::stream_timeout);
#endif
#ifdef ETXTBSY
PP_NET_ERROR(TextFileBusyError, std::errc::text_file_busy);
#endif
PP_NET_ERROR(TimedOutError, std::errc::timed_out);
PP_NET_ERROR(TooManyFilesOpenInSystemError, std::errc::too_many_files_open_in_system);
PP_NET_ERROR(TooManyFilesOpenError, std::errc::too_many_files_open);
PP_NET_ERROR(TooManyLinksError, std::errc::too_many_links);
PP_NET_ERROR(TooManySymbolicLinkLevelsError, std::errc::too_many_symbolic_link_levels);
#ifdef EOVERFLOW
PP_NET_ERROR(ValueTooLargeError, std::errc::value_too_large);
#elif defined __AVR__
PP_NET_ERROR(ValueTooLargeError, std::errc::value_too_large);
#endif
PP_NET_ERROR(WrongProtocolTypeError, std::errc::wrong_protocol_type);

RLIB_END