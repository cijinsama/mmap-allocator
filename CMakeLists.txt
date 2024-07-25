cmake_minimum_required(VERSION 3.0)

PROJECT(mmap_allocator
        LANGUAGES CXX
				VERSION 1.0.0)

################
# cmake config #
################

set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "C++ Standard Requirement")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "C++ Extensions")

##############
# dependency #
##############
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

##########
# target #
##########

file(GLOB_RECURSE MMAP_ALLOCATOR_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_library(${PROJECT_NAME} STATIC ${MMAP_ALLOCATOR_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
                               $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                               $<INSTALL_INTERFACE:${CMAKE_INSTALL_FULL_INCLUDEDIR}>)

###########
# install #
###########

# 安装目标和导出设置
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
				LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# 安装头文件
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# 安装配置文件和导出目标
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

configure_file(${PROJECT_NAME}Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

export(EXPORT ${PROJECT_NAME}Targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${PROJECT_NAME}::
)

#############
# FetchContent #
#############

# 处理被FetchContent引入的情况
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(FETCHCONTENT_QUIET OFF)
else()
    set(FETCHCONTENT_QUIET ON)
endif()

if(NOT FETCHCONTENT_QUIET)
    message(STATUS "Fetching ${PROJECT_NAME}")
endif()
