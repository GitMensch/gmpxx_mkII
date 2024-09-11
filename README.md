# gmpxx_mkII.h: A GMP C++ Wrapper for High-Precision Calculations

## Overview

`gmpxx_mkII.h` is a C++ class designed to facilitate high-precision arithmetic operations using the GMP library, which is licensed under the 2-clause BSD license. GMP is a C library for multiple-precision floating-point computations. This class provides a convenient, alternative C++ wrapper around the GMP library's functionalities.

## Features

- **High-Level Source Compatibility:** Highly compatible with `gmpxx.h`, ensuring a smooth transition from the original GMP C++ wrapper.
- **Provides three modes**: mkII mode (default), mkIISR mode (no-precision-change-mode; usually faster than original `gmpxx.h`), and compatibility mode (does not use namespace and no enhancements)
- **Comprehensive Mathematical Functions:** This includes implementations of trigonometric functions (sin, cos, tan, asin, acos, atan) and transcendental functions (log, exp), enhancing the library's utility for complex calculations.
- **Straightforward Coding Style:** Implemented as typical classes without using (very complex) macros or lazy evaluation, prioritizing clarity and maintainability in the code.
- **Header-Only Library:** This library eliminates the need for the `libgmpxx` library, simplifying integration and deployment.
- **Licensing:** Distributed under the 2-clause BSD License, offering flexibility for both open-source and proprietary use.
- **Platform Support:** Optimized for 64-bit Linux and macOS in LP64 environments, ensuring reliable performance across major systems.
- **Original Development:** Written entirely from scratch, providing a clean, optimized, and maintainable code base.

## Requirements

- 64bit linux and 64bit macOS (LP64 environments)
- C++17 or higher

## Installation

To install this library, first clone the repository and then use the make install command:

```bash
git clone https://github.com/nakatamaho/gmpxx_mkII.git
sudo make PREFIX=/usr/local install
```

This will copy `gmpxx_mkII.h` to the appropriate location on your system.

## Usage

To effectively use `gmpxx_mkII` in your C++ projects, you must adjust your include directives and possibly namespace usage depending on the mode you choose to operate in.

- **mkII mode (Default)**: This mode provides enhanced functionalities and optimizations over the original `gmpxx.h`.
  
  ```cpp
  #include <gmpxx_mkII.h>
  using namespace gmp;  // Simplifies access to the library's functionalities
  ```
  
  This setup allows you to use all the functions and classes in `gmpxx_mkII` without needing to prefix them with `gmp::`.

- **mkIISR mode (No-Precision-Change Mode)**: Designed for scenarios where precision settings must be explicitly controlled, this mode assumes changes to precision are made only through environment variables or directly at runtime during the main function's execution, ensuring that the library does not make any automatic adjustments.
  
  ```cpp
  #include <gmpxx_mkII.h>
  #define ___GMPXX_MKII_NOPRECCHANGE___  // Enable mkIISR mode at the preprocessor level
  using namespace gmp;
  ```
  
  In this mode, make sure to define `___GMPXX_MKII_NOPRECCHANGE___` before including the header file to activate the specific functionalities.

- **Compatibility Mode**:
  ```cpp
  #include <gmpxx_mkII.h>
  ```
  Compatibility Mode is designed for those who require strict backward compatibility with older versions of the `gmpxx.h` library. When compiling your project, ensure to include the flags `-D___GMPXX_POSSIBLE_BUGS___` and `-D___GMPXX_STRICT_COMPATIBILITY___` to activate this mode. This setup avoids the use of namespaces and maintains behavior consistent with earlier library versions.

In Compatibility Mode, do not use `using namespace gmp;` to avoid namespace conflicts. This mode ensures that your existing code that relies on older `gmpxx.h` features works without modifications.

## Link

When linking your project with `gmpxx_mkII.h`, it is advisable to remove the -lgmpxx link option that was used with the original GMP C++ wrapper. While keeping it may not cause immediate harm, removing it ensures that you are linking specifically against the correct library version provided by gmpxx_mkII, avoiding any potential conflicts or ambiguities.

## Improvements from original gmpxx.h

One of the key enhancements in `gmpxx_mkII` over the original `gmpxx.h` is the extension of mathematical functions without the limitations previously noted in the GMP C++ interface. The updated version includes a broader range of functions such as `log`, `log2`, `log10`, `exp`, `pow`, `cos`, `sin`, `asin`, `acos`, `atan`, `atan2`, `cosh`, `sinh`, `tanh`, `acosh`, `asinh`, and `atanh`. These improvements allow for more robust and versatile mathematical computations, effectively removing the restrictions detailed in the [GMP C++ Interface Limitations](https://gmplib.org/manual/C_002b_002b-Interface-Limitations). This enhancement ensures that users have access to a more comprehensive and unrestricted set of tools for high-precision calculations.

## Compatibility Differences from Original gmpxx.h

`gmpxx_mkII` introduces several modifications to behavior and functionality when compared to the original `gmpxx.h`. These changes are designed to improve predictability and align more closely with standard C++ practices, but they also affect how certain operations are handled:

- **No Binary Compatibility**:
  `gmpxx_mkII` does not maintain binary compatibility with `gmpxx.h`. This means that binaries compiled with the original library cannot be directly replaced with those compiled using `gmpxx_mkII`. This allows for architectural improvements and the introduction of new features.

- **Difference in Precision Handling in Evaluations**:
  ```cpp
  const int small_prec = 64, medium_prec = 128, very_large_prec = 256;
  mpf_set_default_prec(medium_prec);
  mpf_class f(3.0, small_prec);
  mpf_class g(1 / f, very_large_prec);
  ```
  Unlike `gmpxx.h` where the precision of an expression is lazily evaluated upon assignment, `gmpxx_mkII` evaluates expressions immediately with the precision of the variable being assigned. This means in `gmpxx_mkII`, the expression `1/f` is evaluated with `small_prec`, then assigned to `g` at `very_large_prec`, ensuring more predictable behavior.

- **Difference in Precision Assignment in Random Number Generation**:
  ```cpp
  const int medium_prec = 128, large_prec = 512;
  mpf_set_default_prec(medium_prec);
  gmp_randclass r1(gmp_randinit_default);
  mpf_class f(0, large_prec);
  f = r1.get_f();
  ```
  In `gmpxx_mkII`, random numbers are generated at the default precision (`medium_prec`), not the precision of the variable `f` (`large_prec`) as in `gmpxx.h`. This modification aligns with typical C++ assignment behaviors, where the right-hand side of an assignment does not adapt to the left side's attributes.

Each of these changes enhances consistency and reduces complexity, making `gmpxx_mkII` a more robust and straightforward tool for high-precision computations. However, users migrating from `gmpxx.h` should be aware of these differences to adjust their code accordingly.


## Contributing

Contributions to the gmpxx_mkII.h are welcome. Please submit pull requests or open issues to suggest improvements or report bugs.

## License

This project is licensed under the 2-clause BSD License.

## ChatGPT4 (memo)

* https://chat.openai.com/c/e88b85d9-dbca-4bdc-bfb3-52cff97ddae4
* https://chat.openai.com/c/268fe353-3a3f-44ea-8519-987b674d7d12
* https://chat.openai.com/c/46a93858-ea63-462f-b392-b9ed3a717454
* https://chat.openai.com/c/e472fda8-1397-44de-bef5-09acb143dbcf
