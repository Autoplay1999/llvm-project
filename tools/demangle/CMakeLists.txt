cmake_minimum_required(VERSION 3.20)
project(LLVMDemangleUtility CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure MSVC runtime library statically (/MT or /MTd)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Locate Demangle sources relative to this folder
set(LLVM_DEMANGLE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../llvm/lib/Demangle")
set(LLVM_DEMANGLE_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../llvm/include")

set(DEMANGLE_SOURCES
    "${LLVM_DEMANGLE_SRC_DIR}/Demangle.cpp"
    "${LLVM_DEMANGLE_SRC_DIR}/DLangDemangle.cpp"
    "${LLVM_DEMANGLE_SRC_DIR}/ItaniumDemangle.cpp"
    "${LLVM_DEMANGLE_SRC_DIR}/MicrosoftDemangle.cpp"
    "${LLVM_DEMANGLE_SRC_DIR}/MicrosoftDemangleNodes.cpp"
    "${LLVM_DEMANGLE_SRC_DIR}/RustDemangle.cpp"
)

add_library(LLVMDemangle STATIC ${DEMANGLE_SOURCES})

target_include_directories(LLVMDemangle PUBLIC
    "${LLVM_DEMANGLE_INC_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(MSVC)
    target_compile_options(LLVMDemangle PRIVATE
        /GS-
        /sdl-
        /GR-
        /W4
    )
endif()

add_executable(demangle src/main.cpp)
target_link_libraries(demangle PRIVATE LLVMDemangle)

if(MSVC)
    target_compile_options(demangle PRIVATE
        /GS-
        /sdl-
        /GR-
        /W4
    )
endif()

include(FetchContent)
FetchContent_Declare(
    doctest
    URL            https://github.com/doctest/doctest/archive/refs/tags/v2.4.11.zip
)
FetchContent_MakeAvailable(doctest)

add_executable(demangle_tests tests/test_main.cpp)
target_link_libraries(demangle_tests PRIVATE LLVMDemangle doctest::doctest)
target_include_directories(demangle_tests PRIVATE "${doctest_SOURCE_DIR}/doctest")

if(MSVC)
    target_compile_options(demangle_tests PRIVATE
        /GS-
        /sdl-
        /GR-
        /W4
    )
endif()

enable_testing()
add_test(NAME DemangleUnitTests COMMAND demangle_tests)
