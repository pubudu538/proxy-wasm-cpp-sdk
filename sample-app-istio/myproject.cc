#include <string>
#include <string_view>
#include <unordered_map>

#include "proxy_wasm_intrinsics.h"

#include "google/protobuf/util/json_util.h"

using google::protobuf::util::JsonParseOptions;


class ExampleRootContext : public RootContext {
public:
  explicit ExampleRootContext(uint32_t id, std::string_view root_id) : RootContext(id, root_id) {}

  bool onStart(size_t) override;
  bool onConfigure(size_t) override;

  echo::Config config_;
};

class ExampleContext : public Context {
public:
  explicit ExampleContext(uint32_t id, RootContext* root) : Context(id, root) {}

  FilterHeadersStatus onRequestHeaders(uint32_t headers, bool end_of_stream) override;
  void onDone() override;

};
static RegisterContextFactory register_ExampleContext(CONTEXT_FACTORY(ExampleContext),
                                                        ROOT_FACTORY(ExampleRootContext));


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

// bool ExampleRootContext::onConfigure(size_t) {
//   logInfo("onConfigure");
//   proxy_set_tick_period_milliseconds(1000); // 1 sec
//   return true;
// }

bool ExampleRootContext::onConfigure(size_t config_size) {
  LOG_INFO("onConfigure called");
  logInfo("onConfigure");
  proxy_set_tick_period_milliseconds(1000); // 1 sec
  const WasmDataPtr configuration = getBufferBytes(WasmBufferType::PluginConfiguration, 0, config_size);

    JsonParseOptions json_options;
    const Status options_status = JsonStringToMessage(
        configuration->toString(),
        &config_,
        json_options);
    if (options_status != Status::OK) {
      LOG_WARN("Cannot parse plugin configuration JSON string: " + configuration->toString());
      return false;
    }
    LOG_INFO("Loading Config: " + config_.clustername());
  return true;
}