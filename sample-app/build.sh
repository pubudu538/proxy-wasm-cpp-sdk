
bazel build istio_example.wasm
cp ../bazel-bin/sample-app/istio_example.wasm ./

date_value=$(date)
git commit -a -m "$date_value"
git push pubudu master

sha256sum istio_example.wasm