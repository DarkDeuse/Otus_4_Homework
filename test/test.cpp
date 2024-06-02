#include <gtest/gtest.h>
#include "../lib/version.h"
#include "../inc/print.h"

TEST(lib, version) {
    ASSERT_GT(version(), 0);
}

// othet test

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}