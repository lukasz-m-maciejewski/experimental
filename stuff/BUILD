cc_binary(
    name = "example",
    srcs = ["example.cpp"],
)

cc_binary(
    name = "multivariant",
    srcs = ["multivariant.cpp"],
)

cc_library(
    name = "fsm",
    hdrs = ["fsm.hpp"],
)

cc_binary(
    name = "vending_machine",
    srcs = ["vending_machine.cpp"],
    deps = [
        ":fsm",
    ]
)
