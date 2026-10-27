*This activity has been created as part of the 42 curriculum by suobeida*

# ft_printf

## Description

ft_printf is a re-implementation of the C `printf()` function, built as a
static library (`libftprintf.a`). The goal is to learn variadic functions
(`<stdarg.h>`), format parsing and modular C, without the buffer management
of the original.

```c
int	ft_printf(const char *format, ...);
```

It returns the number of characters written, or `-1` if `format` is `NULL`.

**Supported conversions:** `%c` (character), `%s` (string, `(null)` if NULL),
`%p` (pointer in hex, `(nil)` if NULL), `%d` / `%i` (signed decimal),
`%u` (unsigned decimal), `%x` / `%X` (hex, lower/upper case), `%%` (percent).

**Files:**

| File              | Functions                | Role                                                   |
|-------------------|--------------------------|--------------------------------------------------------|
| `ft_printf.h`     | -                        | Includes and prototypes                                |
| `ft_printf.c`     | `ft_printf`, `ft_convert`| Format scanning, argument fetching and dispatch        |
| `ft_print_text.c` | `ft_putchar`, `ft_putstr`| `%c`, `%s` and `%%` output, and the character writer   |
| `ft_print_num.c`  | `ft_putnbr`              | `%d` and `%i`: signed decimal, handles `INT_MIN`       |
| `ft_print_unbr.c` | `ft_putunbr`             | `%u`: unsigned decimal                                 |
| `ft_print_hex.c`  | `ft_puthex`              | `%x` and `%X`: hexadecimal, case chosen by a flag      |
| `ft_print_ptr.c`  | `ft_putptr`, `ft_puthexa`| `%p`: `0x` prefix plus address in hex (`ft_puthexa` is static) |

## Instructions

```bash
make            # builds libftprintf.a with ar
make clean      # removes object files
make fclean     # removes objects and the library
make re         # fclean + all
```

Use it in your own program:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello %s, number %d, hex %x\n", "world", 42, 255);
	return (0);
}
```

```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o demo && ./demo
```

## Algorithm and data structure

The format string is scanned once, left to right. Normal characters are
written directly with `ft_putchar`. After a `%` (with a character following
it), `ft_convert` reads the matching argument with `va_arg` using the type
the specifier requires (`int` for `%c`, `%d`, `%i`; `unsigned int` for `%u`,
`%x`, `%X`; `char *` for `%s`; `void *` for `%p`) and calls the right printer.
`%%` consumes no argument. Every printer returns the number of bytes it
wrote, and the totals are added up, so the return value is exact.

Numbers are printed recursively, with no buffer or array: the function prints
`n / base` first, then the last digit, so digits come out in the right order.
Each conversion has its own small recursive printer:

- `ft_putnbr` (base 10, signed): prints `-` for negative values and negates
  the number. `INT_MIN` cannot be negated in an `int`, so it is handled as a
  special case and printed directly.
- `ft_putunbr` (base 10, unsigned): the same recursion on an `unsigned int`.
- `ft_puthex` (base 16): the digit set (`0123456789abcdef` or
  `0123456789ABCDEF`) is picked by an `upper` flag, so `%x` and `%X` share
  one function.
- `ft_putptr`: prints `(nil)` for a NULL pointer, otherwise `0x` followed by
  the address as an `unsigned long`, printed by the static helper
  `ft_puthexa` (64 bits are needed, so `unsigned int` would truncate it).

The `va_list` is passed by pointer (`va_list *`) so all helpers consume the
same argument list. A trailing lone `%` at the end of the string is printed as
a normal character instead of reading past the end. No data structure is
needed: the design is a single pass with no allocation, so nothing can leak.

## Resources

- `man 3 printf`, `man 3 stdarg`, `man 2 write`
- [GNU C Library manual: formatted output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html)
- [cppreference: variadic functions](https://en.cppreference.com/w/c/variadic)
- [GNU Make manual](https://www.gnu.org/software/make/manual/make.html)
- [42 Norm (norminette)](https://github.com/42School/norminette)

**AI usage:** AI (Claude) was used to explain how `va_list` works, to suggest
the file split and the recursive printing approach, to help interpret
compiler, valgrind and tester output while debugging, and to deepen my
understanding of how `printf` works. All code was reviewed, tested against the
real `printf`, and is understood by the author.
