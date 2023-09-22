file(GLOB SRCS_G "src/*.cpp")
RLIB_SOURCES_AUTO(SRCS ${SRCS_G})

file(GLOB_RECURSE HDRS_G "include/*.h")
RLIB_HEADERS_AUTO(SRCS ${HDRS_G})

add_library(Http ${SRCS})
add_library(Rlib::Http ALIAS Http)
set_target_properties(Http
    PROPERTIES
     LINKER_LANGUAGE CXX
     OUTPUT_NAME RlibHttp
	 DEFINE_SYMBOL Http_EXPORTS
)
target_include_directories(Http
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Http PUBLIC Rlib::Net)

if(NOT BUILD_SHARED_LIBS)
	target_compile_definitions(Http
		PUBLIC
			RLIB_STATIC
	)
endif()

if(ENABLE_TESTS)
	add_subdirectory(samples)
endif()