#include "src/runtime/runtime-utils.h"

#include <memory>
#include <sstream>

#include "src/api-inl.h"
#include "src/arguments-inl.h"
#include "src/assembler-inl.h"
#include "src/base/platform/mutex.h"
#include "src/compiler-dispatcher/optimizing-compile-dispatcher.h"
#include "src/compiler.h"
#include "src/counters.h"
#include "src/deoptimizer.h"
#include "src/frames-inl.h"
#include "src/heap/heap-inl.h"  // For ToBoolean. TODO(jkummerow): Drop.
#include "src/heap/heap-write-barrier-inl.h"
#include "src/ic/stub-cache.h"
#include "src/isolate-inl.h"
#include "src/objects/heap-object-inl.h"
#include "src/objects/smi.h"
#include "src/ostreams.h"
#include "src/runtime-profiler.h"
#include "src/snapshot/natives.h"
#include "src/trap-handler/trap-handler.h"
#include "src/wasm/memory-tracing.h"
#include "src/wasm/module-compiler.h"
#include "src/wasm/wasm-engine.h"
#include "src/wasm/wasm-module.h"
#include "src/wasm/wasm-objects-inl.h"
#include "src/wasm/wasm-serialization.h"

namespace v8 {
namespace internal {

RUNTIME_FUNCTION(Runtime_InvokeDynamic) {
  DCHECK_EQ(1, args.length());
  CONVERT_ARG_HANDLE_CHECKED(String,arg_string,0);
  
  std::string  params(arg_string->ToCString().get());
  int result = isolate->dynamic_function()->invoke(params.c_str());
  
  return Smi::FromInt(result);
}

}  // namespace internal
}  // namespace v8
