CC_FLAGS = [
    "-std=c++20",
    "-Wall",
    "-Wpedantic",
    "-Wunused-value",
]

cc_library(
    name = "minitest",
    hdrs = ["testing.h"],
)


cc_binary(
    name = "chapter2",
    srcs = ["chapter2.cc"],
    copts = CC_FLAGS,
    deps = [
        "@fmt",
        "minitest"
    ],
)


cc_binary(
    name = "chapter3",
    srcs = ["chapter3.cc", "timeit.h"],
    copts = CC_FLAGS,
    deps = [
        "@fmt",
    ],
)

cc_binary(
    name = "chapter4",
    srcs = ["chapter4.cc", "timeit.h"],
    copts = CC_FLAGS,
    deps = [
        "@fmt",
        "minitest",
    ],
)