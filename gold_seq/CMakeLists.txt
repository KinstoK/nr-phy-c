# 1. 创建静态库 gold_seq_lib（用于其他模块链接）
add_library(gold_seq_lib STATIC gold_seq.c)
target_include_directories(gold_seq_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 2. 创建可执行测试程序（用来调试 gold_seq 库）
add_executable(gold_seq test_gold_seq.c)
target_link_libraries(gold_seq PRIVATE gold_seq_lib)
target_link_libraries(gold_seq_lib PUBLIC m)
