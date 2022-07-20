## Passing custom module from js to C++ code
I created a tiny exaple to show how to pass module from JS to C++ using Emscripten and `val::global()`

#### Description
First of all we need to write a C++ function for the loading. It looks like this:
```cpp
int loadCustomModule (std::string globalModuleName) {
  val ModuleClass = val::global(globalModuleName.c_str());
    if (!ModuleClass.as<bool>()) {
    std::cout << "No global module " << globalModuleName;
  }
  return 0;
}
```
Then we need to pass this function to JS using `EMSCRIPTEN_BINDINGS`:
```
EMSCRIPTEN_BINDINGS(module) {
  function("loadCustomModule", &loadCustomModule);
}
```
Yeah, that's all! Now, we can use our `loadCustomModule` function in JS.
```js
class HelloWorldCustomModule {
    helloWorld() {
        console.log('Hello, World!')
    }
}
var Module = {
    onRuntimeInitialized: function () {
        window.HelloWorldCustomModule = HelloWorldCustomModule;
        Module.loadCustomModule('HelloWorldCustomModule')
    }
};
``` 

And the last step is using our `HelloWorldCustomModule` in C++
```cpp
int loadCustomModule (std::string globalModuleName) {
  // ... first part is above
  val module = ModuleClass.new_();
  module.call<val>("helloWorld");
  return 0;
}
```

#### Compilation
```
em++ -lembind -o passCustomModule.js passCustomModule.cpp -s ERROR_ON_UNDEFINED_SYMBOLS=0 -Wall --bind
```
