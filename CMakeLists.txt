cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

# Note: update this to your new project's name and version
project(
  lu
  VERSION 1.0
  LANGUAGES C CXX)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)
include(cmake/cpm_ws.cmake)

CPM_WSRefPackage(
	boostorg
	boost)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx")
	
file(GLOB_RECURSE sources CONFIGURE_DEPENDS 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/*.cxx")

# ---- Create library ----

add_library(lu ${headers} ${sources})

#target_compile_options(lu INTERFACE "$<$<C_COMPILER_ID:MSVC>:/utf-8>")
#target_compile_options(lu INTERFACE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set_target_properties(lu PROPERTIES CXX_STANDARD 20)

target_compile_definitions(lu 
	PUBLIC
		SPDLOG_COMPILED_LIB=1)

# being a cross-platform target, we enforce standards conformance on MSVC
#target_compile_options(lu PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
if(WIN32 OR CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
	target_link_libraries(lu PUBLIC 
		Userenv.lib)
endif()

target_link_libraries(lu PUBLIC 
	boost_config 
	boost_accumulators 
	boost_algorithm 
	boost_align 
	boost_asio 
	boost_assert 
	boost_assign 
	boost_container 
	boost_core 
	boost_crc 
	boost_dll 
	boost_dynamic_bitset 
	boost_interprocess 
	boost_leaf 
	boost_lockfree 
	boost_outcome 
	boost_pool
	boost_predef
	boost_preprocessor
	boost_process
	boost_program_options
	boost_scope_exit
	boost_static_string
	boost_system
	boost_tokenizer
	boost_type_erasure
	boost_type_index
	boost_type_traits
	boost_typeof
	boost_units
	boost_uuid
	boost_vmd)

target_include_directories(lu 
	PUBLIC 
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
		${PROJECT_SOURCE_DIR}/include/memory)

add_library(loopunit::lu ALIAS lu)
