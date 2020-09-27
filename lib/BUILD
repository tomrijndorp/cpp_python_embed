cc_library(
    name = 'lib',
    hdrs = glob(['include/**/*.hpp']),
    srcs = glob(['*.cpp']),
    strip_include_prefix = 'include',
    include_prefix = 'lib',
    visibility = ['//visibility:public'],
)

cc_test(
    name = 'test_lib',
    srcs = ['test/test_foo.cpp'],
    deps = [
        ':lib',
        '@googletest//:gtest_main',
    ],
)