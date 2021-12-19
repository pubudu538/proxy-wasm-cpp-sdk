#include <string>
#include <unordered_map>

#include "proxy_wasm_intrinsics.h"

class ExampleRootContext : public RootContext {
public:
  explicit ExampleRootContext(uint32_t id, std::string_view root_id) : RootContext(id, root_id) {}

  bool onStart(size_t) override;
  bool onConfigure(size_t) override;
};

class ExampleContext : public Context {
public:
  explicit ExampleContext(uint32_t id, RootContext* root) : Context(id, root) {}

  FilterHeadersStatus onRequestHeaders(uint32_t headers, bool end_of_stream) override;
  void onDone() override;
};
static RegisterContextFactory register_ExampleContext(CONTEXT_FACTORY(ExampleContext));

FilterHeadersStatus ExampleContext::onRequestHeaders(uint32_t headers, bool end_of_stream) {
  logInfo(std::string("onRequestHeaders ") + std::to_string(id()));
  auto path = getRequestHeader(":path");
  logInfo(std::string("header path ") + std::string(path->view()));
  addResponseHeader("X-Wasmss-custom", "FOO");
  return FilterHeadersStatus::Continue;
}

void ExampleContext::onDone() { logInfo("onDone " + std::to_string(id())); }

bool ExampleRootContext::onStart(size_t) {
  logInfo("onStart");
  return true;
}

bool ExampleRootContext::onConfigure(size_t) {
  logInfo("onConfigure");
  proxy_set_tick_period_milliseconds(1000); // 1 sec
  return true;
}