project(testclient)

file(GLOB_RECURSE app_src src/*.cpp)

add_executable(testclient ${app_src})
target_link_libraries(testclient wpiutil ntcore)

set_property(TARGET testclient PROPERTY FOLDER "executables")
