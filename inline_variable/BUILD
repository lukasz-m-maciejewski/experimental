cc_library(
    name = "unit1",
    srcs = [  "unit1.cpp" ],
)

cc_library(
    name = "unit2",
    srcs = [ "unit2.cpp" ],
)

cc_binary(
    name = "main",
    srcs = [ "main.cpp" ],
    deps = [ ":unit1", ":unit2" ],
)
