#include <catch2/catch.hpp>
#include <version.h>

TEST_CASE("Version info not empty", "[single-file]" ) {
    REQUIRE(VersionHelper::getInstance().AppName != "");
    REQUIRE(VersionHelper::getInstance().CommitHash != "");
}
