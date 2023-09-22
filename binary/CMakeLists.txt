file(GLOB SRCS_G "src/*.cpp")
RLIB_SOURCES_AUTO(SRCS ${SRCS_G})

file(GLOB_RECURSE HDRS_G "include/*.h")
RLIB_HEADERS_AUTO(SRCS ${HDRS_G})


add_library(Binary ${SRCS})
add_library(Rlib::Binary ALIAS Binary)
set_target_properties(Binary
    PROPERTIES
	 LINKER_LANGUAGE CXX
     OUTPUT_NAME RlibBinary
	 DEFINE_SYMBOL Binary_EXPORTS
)
target_include_directories(Binary
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(NOT BUILD_SHARED_LIBS)
	target_compile_definitions(Binary
		PUBLIC
			RLIB_STATIC
	)
endif()