// Copyright (c) 2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_RESULT_H
#define BITCOIN_RESULT_H

#include <utility>

/**
 * Success represents a successful result.
 *
 * Example:
 *     Result<std::string, void> foo() {
 *         return Success<std::string>("whoot");
 *     }
 */
template<typename T>struct Success
{
    T value;
    Success(const T& v) : value{v} {}
    Success(T&& v) : value{std::move(v)} {}
};

/**
 * Success<void> is a specialization of Success<T> that represents a successful result without a value.
 *
 * Example:
 *     Result<void, std::string> foo() {
 *         return Success<void>();
 *     }
 */
template<>struct Success<void>{};

/**
 * Error represents an error.
 *
 * Example:
 *     Result<void, std::string> foo() {
 *         return Error<std::string>("Something went wrong");
 *     }
 */
template<typename E>struct Error
{
    E value;
    Error(const E& v) : value{v} {}
    Error(E&& v) : value{std::move(v)} {}
};

/**
 * Error<void> is a specialization of Error<T> that represents an error without a value.
 *
 * Example:
 *     Result<std::string, void> foo() {
 *         return Error<void>();
 *     }
 */
template<>struct Error<void>{};

/**
 * Result is a type that represents either success or failure.
 *
 * Example:
 *     Result<int, std::string> r = foo();
 *     if (r.success) {
 *         std::cout << "Result: " << r.success_value << std::endl;
 *     } else {
 *         std::cout << "Error: " << r.error_value << std::endl;
 *     }
 */
template<typename T, typename E>struct Result
{
    bool success;

    T success_value;
    E error_value;

    Result(Success<T> s) : success{true}, success_value{std::move(s.value)} {}
    Result(Error<E> e) : success{false}, error_value{std::move(e.value)} {}
};

/**
 * Result<void, E> is a specialization of Result<T, E> that represents a result without a success value.
 *
 * Example:
 *     Result<void, HTTPStatusCode> r = foo();
 *     if (r.success) {
 *         std::cout << "OK" << std::endl;
 *     } else {
 *         std::cout << "Error: " << r.error_value << std::endl;
 *     }
 */
template<typename E>struct Result<void, E>
{
    bool success;
    E error_value;

    Result(Success<void> s) : success{true} {}
    Result(Error<E> e) : success{false}, error_value{std::move(e.value)} {}
};

/**
 * Result<T, void> is a specialization of Result<T, E> that represents a result without an error value.
 *
 * Example:
 *     Result<int, void> r = foo();
 *     if (r.success) {
 *         std::cout << "Result: " << r.success_value << std::endl;
 *     } else {
 *         std::cout << "Error: " << r.error_value << std::endl;
 *     }
 */
template<typename T>struct Result<T, void>
{
    bool success;
    T success_value;

    Result(Success<T> s) : success{true}, success_value{std::move(s.value)} {}
    Result(Error<void> e) : success{false} {}
};

#endif
