﻿# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
add_definitions(-DSPDLOG_COMPILED_LIB)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}\\spdlog\\include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}\\asio\\include)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}\\spdlog\\lib\\spdlogd.lib)

project ("ARINC615A-api")

# 包含子项目。
add_subdirectory ("ARINC615A-api")
