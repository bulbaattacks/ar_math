#pragma once
#include <climits>

namespace ar_math
{

enum class Status
{
    Ok = 0,
    InvalidArgument = -1,
    Overflow = -2,
};

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
        return Status::InvalidArgument;
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
        return Status::InvalidArgument;
    }

    if (a <= 1)
    {
        result = 1;
        return Status::Ok;
    }

    int previousResult = 0;
    Status status = factorial(a - 1, previousResult);

    if (status != Status::Ok)
    {
        return status;
    }

    if (a > INT_MAX / previousResult)
    {
        return Status::Overflow;
    }
    result = a * previousResult;
    return Status::Ok;
}

inline Status power(int a, int b, int& result)
{
    if (b < 0)
    {
        return Status::InvalidArgument;
    }

    if (a == INT_MAX && b > 1)
    {
        return Status::Overflow;
    }

    result = 1;
    for (int i = 1; i <= b; i++)
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

} // namespace math
