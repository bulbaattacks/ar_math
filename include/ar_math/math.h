#pragma once
#include <climits>

namespace ar_math
{

enum class Status
{
    Ok = 0,
    Overflow = -1,
    DivisionByZero = -2,
    NegativeArgument = -3,
    UnknownOperation = -4,
    InitialStatus = -5,
};

namespace detail
{
inline Status factorialStep(int i, int n, int& acc)
{
    if (i > n)
    {
        return Status::Ok;
    }

    if (acc > INT_MAX / i)
    {
        return Status::Overflow;
    }
    acc *= i;
    return factorialStep(i + 1, n, acc);
}

} // namespace detail

inline Status addition(int a, int b, int& result)
{
    if (a > 0 && b > 0)
    {
        if (a > INT_MAX - b)
        {
            return Status::Overflow;
        }
    }

    if (a < 0 && b < 0)
    {
        if (a < INT_MIN - b)
        {
            return Status::Overflow;
        }
    }

    result = a + b;
    return Status::Ok;
}

inline Status subtraction(int a, int b, int& result)
{

    if (b < 0)
    {
        if (a > INT_MAX + b)
        {
            return Status::Overflow;
        }
    }

    if (b > 0)
    {
        if (a < INT_MIN + b)
        {
            return Status::Overflow;
        }
    }

    result = a - b;
    return Status::Ok;
}

inline Status division(int a, int b, int& result)
{
    if (b == 0)
    {
        return Status::DivisionByZero;
    }

    if (a == INT_MIN && b == -1)
    {
        return Status::Overflow;
    }
    result = a / b;
    return Status::Ok;
}

inline Status multiplication(int a, int b, int& result)
{

    if (a > 0 && b > 0)
    {
        if (a > INT_MAX / b)
        {
            return Status::Overflow;
        }
    }

    if (a < 0 && b < 0)
    {
        if (a < INT_MAX / b)
        {
            return Status::Overflow;
        }
    }

    if (a < 0 && b > 0)
    {
        if (a < INT_MIN / b)
        {
            return Status::Overflow;
        }
    }

    if (a > 0 && b < 0)
    {
        if (b < INT_MIN / a)
        {
            return Status::Overflow;
        }
    }

    result = a * b;
    return Status::Ok;
}

inline Status factorial(int a, int& result)
{

    if (a < 0)
    {
        return Status::NegativeArgument;
    }

    int acc = 1;
    int start = 2;

    Status status = detail::factorialStep(start, a, acc);
    if (status == Status::Ok)
    {
        result = acc;
    }

    return status;
}

inline Status power(int a, int b, int& result)
{
    if (b < 0)
    {
        return Status::NegativeArgument;
    }

    if (b == 0)
    {
        result = 1;
        return Status::Ok;
    }

    if (a == 0 || a == 1)
    {
        result = a;
        return Status::Ok;
    }

    if (a == -1)
    {
        if (b % 2 == 0)
        {
            result = 1;
        }
        else
        {
            result = -1;
        }
        return Status::Ok;
    }

    result = 1;

    for (int i = 0; i < b; i++)
    {
        if (a > 0)
        {
            if (a > INT_MAX / result)
            {
                return Status::Overflow;
            }
        }

        if (a < 0)
        {
            if (result > 0)
            {
                if (a < INT_MIN / result)
                {
                    return Status::Overflow;
                }
            }
            if (result < 0)
            {
                if (a < INT_MAX / result)
                {
                    return Status::Overflow;
                }
            }
        }
        result *= a;
    }

    return Status::Ok;
}

} // namespace ar_math
