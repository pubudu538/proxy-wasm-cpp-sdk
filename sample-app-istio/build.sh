docker run -v /Users/pubudu/wso2/sources/proxy-wasm-cpp-sdk/sample-app-istio:/work -w /work  wasmsdk:v2 /build_wasm.sh

date_value=$(date)
git commit -a -m "$date_value"
git push pubudu master

sha256sum myproject.wasm