load("//bazel/wasm:wasm.bzl", "wasm_cc_binary")

### optional imports ###
# To import commonly used libraries from istio proxy, such as base64, json, and flatbuffer.
IO_ISTIO_PROXY_SHA = "a70bc93ce0610007bf5275091c6e7b455d397768"

IO_ISTIO_PROXY_SHA256 = "6621459c49c47f84b96b7bc2797652bc5a94c6a5dc1c89056ef5c38e05303d13"

http_archive(
    name = "io_istio_proxy",
    sha256 = IO_ISTIO_PROXY_SHA256,
    strip_prefix = "proxy-" + IO_ISTIO_PROXY_SHA,
    url = "https://github.com/istio/proxy/archive/" + IO_ISTIO_PROXY_SHA + ".tar.gz",
)

licenses(["notice"])  # Apache 2

wasm_cc_binary(
    name = "istio_example.wasm",
    srcs = ["istio_wasm.cc"],
    deps = [
        "@io_istio_proxy//extensions/common/wasm:json_util",
        "@proxy_wasm_cpp_sdk//:proxy_wasm_intrinsics",
    ],
)
