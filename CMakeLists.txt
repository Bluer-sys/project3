# CMakeList.txt: проект CMake для ip_filter; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable (ip_filter ip_filter.cpp )

set_target_properties (ip_filter PROPERTIES
CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON
COMPILE_OPTIONS "-Wall")

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ilianovi@mail.ru)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
