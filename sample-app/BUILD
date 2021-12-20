load("//bazel/wasm:wasm.bzl", "wasm_cc_binary")

licenses(["notice"])  # Apache 2

wasm_cc_binary(
    name = "istio_example.wasm",
    srcs = ["istio_wasm.cc"],
    deps = [
        "@proxy_wasm_cpp_sdk//:proxy_wasm_intrinsics",
    ],
)
