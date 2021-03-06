#ifndef V8_INVOKE_DYNAMIC_H
#define V8_INVOKE_DYNAMIC_H

#include <string>

#if defined WIN32 || defined _WIN32
#  define DYNAMIC_LOAD_WIN
#elif defined( __APPLE__ ) && defined( __MACH__ )
#  define DYNAMIC_LOAD_MAC
#else
#  define DYNAMIC_LOAD_LINUX
#endif

#define INVOKE_FUNCTION_NAME "invoke"

typedef int(*InvokeFunctionType)(const char*);

namespace v8 {
namespace internal {

class DynamicFunction {
 public:
  int initialize(const char* filepath);
  int invoke(const char* params);
  
 public:
  DynamicFunction();
  ~DynamicFunction();
  
 private:
  int LoadLibrary();
  void ReleaseLibary();
  int GetFunctionAddr();
  
 private:
  std::string file_path_;
  void* library_handle_;
  InvokeFunctionType invoke_function_;
};

} // internal
} // v8

#endif
