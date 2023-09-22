add_executable(SimpleSite src/server.cpp)
target_link_libraries(SimpleSite Rlib::Foundation Rlib::Net Rlib::Http)

file(COPY files/index.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY files/login.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY files/mail_icon.ico DESTINATION ${CMAKE_CURRENT_BINARY_DIR})