cmake_minimum_required(VERSION 3.13)
project(c_cpp_lecture_3rd_year)

set(CMAKE_CXX_STANDARD 14)

# 식사하는 철학자 문제(Deadlock 발생 버전)
add_executable(Dining_Philosophers lecture_operating_system/dining_philosophers.c)
target_link_libraries(Dining_Philosophers pthread)

# 식사하는 철학자 문제(Circular Wait 제거)
add_executable(Dining_Philosophers_Sol1 lecture_operating_system/dining_philosophers_sol1.c)
target_link_libraries(Dining_Philosophers_Sol1 pthread)

# 식사하는 철학자 문제(Deadlock Prevention - No Hold and Wait)
add_executable(Dining_Philosophers_Sol2 lecture_operating_system/dining_philosophers_sol2.c)
target_link_libraries(Dining_Philosophers_Sol2 pthread)