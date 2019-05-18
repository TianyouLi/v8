#include <iostream>
#include "invoke-dynamic.h"

#ifdef DYNAMIC_LOAD_WIN
# include <windows.h>
#else
# include <dlfcn.h>
#endif

namespace v8 {
namespace internal {

DynamicFunction::DynamicFunction():
    library_handle_(NULL), invoke_function_(NULL) {

}

DynamicFunction::~DynamicFunction() {
  ReleaseLibary();
}

int DynamicFunction::LoadLibrary() {
  int result = 0;
  dlerror();
  if (!file_path_.empty()) {
    ReleaseLibary();
  }

#ifdef DYNAMIC_LOAD_WIN
  library_handle_ = LoadLibraryA(file_path_.c_str());
#else
  library_handle_ = dlopen(file_path_.c_str(), RTLD_LAZY);
#endif

  if (library_handle_ == NULL) {
    result = 1;
  }

  return result;
}
  
void DynamicFunction::ReleaseLibary() {
  if (library_handle_) {
#ifdef DYNAMIC_LOAD_WIN
    FreeLibrary(library_handle_);
#else
    dlclose(library_handle_);
#endif

    library_handle_ = NULL;
    invoke_function_ = NULL;
  }
}

int DynamicFunction::GetFunctionAddr() {
  int result = 0;

  if (library_handle_ != NULL) {
    #ifdef DYNAMIC_LOAD_WIN
      invoke_function_ = (InvokeFunctionType)GetProcAddress(
          library_handle_, INVOKE_FUNCTION_NAME);
    #else
      invoke_function_ = (InvokeFunctionType)dlsym(
          library_handle_, INVOKE_FUNCTION_NAME);
    #endif
  }

  if (invoke_function_ == NULL) {
    result = 1;
  }
  return result;
}

int DynamicFunction::initialize(const char* filepath) {
  file_path_ = filepath;

  return LoadLibrary() + GetFunctionAddr(); 
}

int DynamicFunction::invoke(const char* params) {
  int result = 0;

  if (invoke_function_) {
    result = invoke_function_(params);
  }
  
  return result;
}

} // internal
} // v8
