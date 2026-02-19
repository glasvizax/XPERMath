# XPERMath

my custom math library for 3d rendering

## Installation and Usage

### Through FetchContent (recommended)

#### CMakeLists.txt:
```cmake

include(FetchContent)

FetchContent_Declare(
  XPERMath
  GIT_REPOSITORY https://github.com/glasvizax/XPERMath
  GIT_TAG v1.0
  SYSTEM
)

FetchContent_MakeAvailable(XPERMath)

target_link_libraries(MyApp PRIVATE XPER::Math)
```

### Through find_package

#### CMakeLists.txt:
```cmake

set(XPERMath_DIR "" CACHE PATH "Path to XPERMathConfig.cmake")

find_package(XPERMath CONFIG REQUIRED)

target_link_libraries(MyApp PRIVATE XPER::Math)
```

## Template code

```cpp

#include <iostream>
#include <xm/xm.h>

int main()
{
    xm::vec3 v(1.0f, 2.0f, 3.0f);
    xm::mat4 m = xm::perspective(1.0f, 1.0f, 0.1f, 100.0f);

    xm::lookAt(
        xm::vec3(0.0f, 0.0f, 5.0f),
        xm::vec3(0.0f, 0.0f, 0.0f)
    );

    std::cout << "Library compiled successfully\n";
    return 0;
}
```
