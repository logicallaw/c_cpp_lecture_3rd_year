cmake_minimum_required(VERSION 3.13)
project(c_cpp_lecture_3rd_year)

set(CMAKE_CXX_STANDARD 14)

# Race Condition 문제
add_executable(RaceCondition lecture_operating_system/race_condition.c)
target_link_libraries(RaceCondition pthread)

# Producer/Consumer Solution
add_executable(Producer_Consumer_Sol lecture_operating_system/producer_consumer_sol.c)
target_link_libraries(Producer_Consumer_Sol pthread)

# Readers/Writers - Reader Preference
add_executable(ReadersPreference lecture_operating_system/readers_preference.c)
target_link_libraries(ReadersPreference pthread)

# Readers/Writers - Writer Preference
add_executable(WritersPreferenceV1 lecture_operating_system/writers_preference_v1.c)
target_link_libraries(WritersPreferenceV1 pthread)

# Readers/Writers - Writer Preference considering coner case.
add_executable(WritersPreferenceV2 lecture_operating_system/writers_preference_considering_coner_case_v2.c)
target_link_libraries(WritersPreferenceV2 pthread)

# 식사하는 철학자 문제(Deadlock 발생 버전)
add_executable(Dining_Philosophers lecture_operating_system/dining_philosophers.c)
target_link_libraries(Dining_Philosophers pthread)

# 식사하는 철학자 문제(Circular Wait 제거)
add_executable(Dining_Philosophers_Sol1 lecture_operating_system/dining_philosophers_sol1.c)
target_link_libraries(Dining_Philosophers_Sol1 pthread)

# 식사하는 철학자 문제(Deadlock Prevention - No Hold and Wait)
add_executable(Dining_Philosophers_Sol2 lecture_operating_system/dining_philosophers_sol2.c)
target_link_libraries(Dining_Philosophers_Sol2 pthread)

# 식사하는 철학자 문제(Deadlock Prevention - Resource ordering)
add_executable(Dining_Philosophers_Sol3 lecture_operating_system/dining_philosophers_sol3.c)
target_link_libraries(Dining_Philosophers_Sol3 pthread)