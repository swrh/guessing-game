# CMakeLists.txt

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(gg)

include(CTest)

set(CMAKE_CXX_STANDARD 17)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

find_package(Boost 1.71.0 REQUIRED COMPONENTS
	unit_test_framework
	)

file(GLOB_RECURSE gg_SOURCES
	include/*.hpp
	src/*.cpp
	)

file(GLOB_RECURSE app_SOURCES
	app/*.hpp
	app/*.cpp
	)

add_executable(gg
	${app_SOURCES}
	${gg_SOURCES}
	)

target_compile_definitions(gg
	PUBLIC
	PRIVATE
	)

target_link_libraries(gg
	PRIVATE
	)

target_include_directories(gg
	PUBLIC
		include
	)

install(TARGETS gg
	RUNTIME DESTINATION bin
	)

file(GLOB_RECURSE ggtests_SOURCES
	tests/*.hpp
	tests/*.cpp
	)

add_executable(ggtests
	${gg_SOURCES}
	${ggtests_SOURCES}
	)

target_compile_definitions(ggtests
	PUBLIC
	PRIVATE
	)

target_link_libraries(ggtests
	PRIVATE
		Boost::unit_test_framework
	PUBLIC
	)

target_include_directories(ggtests
	PUBLIC
		include
	)

add_test(NAME ggtests
	COMMAND
		./ggtests
	)
