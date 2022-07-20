#include <emscripten/bind.h>
#include <string>
#include <iostream>

using namespace emscripten;

int loadCustomModule (std::string globalModuleName) {
  val ModuleClass = val::global(globalModuleName.c_str());
    if (!ModuleClass.as<bool>()) {
    std::cout << "No global module " << globalModuleName;
  }
  val module = ModuleClass.new_();
  module.call<val>("helloWorld");
  return 0;
}


EMSCRIPTEN_BINDINGS(module) {
  function("loadCustomModule", &loadCustomModule);
}