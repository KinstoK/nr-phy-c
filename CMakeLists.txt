cmake_minimum_required(VERSION 3.10)
project(nr_phy_c LANGUAGES C)          # 项目名称，只使用 C 语言

# 设置 C 标准（如果需要）
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 添加各个子模块目录
# 每个子目录必须包含自己的 CMakeLists.txt
add_subdirectory(gold_seq)             # 假设 gold_seq 目录
# add_subdirectory(other_module)         # 其他模块，按需添加

# 如果顶层目录下也有源文件（比如主程序 main.c），可以在此处编译
# add_executable(nr_phy_main main.c)
# target_link_libraries(nr_phy_main PRIVATE gold_seq other_module)