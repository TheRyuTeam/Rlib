file(GLOB SRCS_G "src/*.cpp")
RLIB_SOURCES_AUTO(SRCS ${SRCS_G})

file(GLOB_RECURSE HDRS_G "include/*.h")
RLIB_HEADERS_AUTO(SRCS ${HDRS_G})

add_library(Net ${SRCS})
add_library(Rlib::Net ALIAS Net)
set_target_properties(Net
    PROPERTIES
     LINKER_LANGUAGE CXX
     OUTPUT_NAME RlibNet
	 DEFINE_SYMBOL Net_EXPORTS
)
target_include_directories(Net
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Net PUBLIC Rlib::Foundation)

if(NOT BUILD_SHARED_LIBS)
	target_compile_definitions(Net
		PUBLIC
			RLIB_STATIC
	)
endif()