#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "llvm/Demangle/Demangle.h"

TEST_CASE("Microsoft Demangling") {
    CHECK(llvm::demangle("?foo@@YAXH@Z") == "void __cdecl foo(int)");
}

TEST_CASE("Itanium Demangling") {
    CHECK(llvm::demangle("_Z3fooi") == "foo(int)");
}

TEST_CASE("Rust Demangling") {
    CHECK(llvm::demangle("_RNvC3foo3bar") == "foo::bar");
}

TEST_CASE("D Demangling") {
    CHECK(llvm::demangle("_Dmain") == "D main");
}
