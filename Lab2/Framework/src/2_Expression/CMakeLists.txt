# project(2_Expression)
# file(GLOB source
#   "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
#   "${CMAKE_CURRENT_SOURCE_DIR}/*.h" 
# )
# add_executable(${PROJECT_NAME} ${source})
# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(${PROJECT_NAME} PUBLIC structures) 

cmake_minimum_required(VERSION 3.10)

project(2_Expression)

# 指定源文件
file(GLOB source
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${source})

# 添加 include 目录，确保能找到所有头文件
target_include_directories(${PROJECT_NAME} PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR} 
  ${CMAKE_SOURCE_DIR}/Framework/include  # 添加此行
)

# 链接结构库
target_link_libraries(${PROJECT_NAME} PUBLIC structures)