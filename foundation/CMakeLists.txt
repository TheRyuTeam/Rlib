file(GLOB SRCS_G "src/*.cpp")
RLIB_SOURCES_AUTO(SRCS ${SRCS_G})

file(GLOB_RECURSE HDRS_G "include/*.h")
RLIB_HEADERS_AUTO(SRCS ${HDRS_G})

add_library(Foundation ${SRCS})
add_library(Rlib::Foundation ALIAS Foundation)
set_target_properties(Foundation
    PROPERTIES
     LINKER_LANGUAGE CXX
     OUTPUT_NAME RlibFoundation
	 DEFINE_SYMBOL Foundation_EXPORTS
)
target_include_directories(Foundation
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(NOT BUILD_SHARED_LIBS)
	target_compile_definitions(Foundation
		PUBLIC
			RLIB_STATIC
	)
endif()
