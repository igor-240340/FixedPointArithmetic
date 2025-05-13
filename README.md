## Fixed Point Arithmetic

Implementation of fixed-point arithmetic using integers.

## Features
- Binary Fixed Point (16.16).
- Decimal Fixed Point (two decimal places for money).

## Usage
### Binary Fixed Point
```cpp
#include <iostream>
#include "Fixed16.h"

int main() {
    Fixed16 a{3.75f};
    Fixed16 b{1.5f};

    Fixed16 sum = a + b;
    Fixed16 diff = a - b;
    Fixed16 prod = a * b;
    Fixed16 quot = a / b;

    std::cout << "a + b = " << sum.to_float() << "\n";
    std::cout << "a - b = " << diff.to_float() << "\n";
    std::cout << "a * b = " << prod.to_float() << "\n";
    std::cout << "a / b = " << quot.to_float() << "\n";

    return 0;
}
```

### Decimal Fixed Point
```cpp
#include <iostream>
#include "Decimal.h"

int main() {
    Decimal a("12.34");
    Decimal b("1.66");

    Decimal sum = a + b;
    Decimal diff = a - b;
    Decimal prod = a * b;
    Decimal quot = a / b;

    std::cout << "a + b = " << sum.to_string() << '\n';
    std::cout << "a - b = " << diff.to_string() << '\n';
    std::cout << "a * b = " << prod.to_string() << '\n';
    std::cout << "a / b = " << quot.to_string() << '\n';

    return 0;
}

```

## Documentation
In /docs directory there are some papers on the topic.

