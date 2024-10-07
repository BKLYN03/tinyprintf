#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/redirect.h>
#include "tinyprintf.h"

// Test helper to redirect output
void redirect_all_stdout(void) 
{
    cr_redirect_stdout();
}

Test(tinyprintf, test_simple_case, .init = redirect_all_stdout) 
{
    int result = tinyprintf("%s [%d] %s", "Hello", 42, "world!");
    cr_assert_stdout_eq_str("Hello [42] world!");
    cr_assert_eq(result, 17);
}

Test(tinyprintf, test_hexadecimal_case, .init = redirect_all_stdout) 
{
    int result = tinyprintf("%s [%x] %s", "Hello", 42, "world!");
    cr_assert_stdout_eq_str("Hello [2a] world!");
    cr_assert_eq(result, 17);
}

Test(tinyprintf, test_octal_case, .init = redirect_all_stdout) 
{
    int result = tinyprintf("Octal: %o", 42);
    cr_assert_stdout_eq_str("Octal: 52");
    cr_assert_eq(result, 10);
}

Test(tinyprintf, test_percent_case, .init = redirect_all_stdout) 
{
    int result = tinyprintf("Print %% sign");
    cr_assert_stdout_eq_str("Print % sign");
    cr_assert_eq(result, 11);
}

Test(tinyprintf, test_null_string_case, .init = redirect_all_stdout) 
{
    int result = tinyprintf("This is a %s", NULL);
    cr_assert_stdout_eq_str("This is a (null)");
    cr_assert_eq(result, 16);
}
