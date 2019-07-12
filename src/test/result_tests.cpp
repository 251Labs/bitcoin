// Copyright (c) 2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <result.h>

#include <test/setup_common.h>
#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(result_type_tests, BasicTestingSetup)

Result<int, std::string>SuccessOrErrorValue(bool success)
{
    if (!success) return Error<std::string>("Error");
    return Success<int>(21000000);
}

Result<void, std::string>SuccessWithoutValueOrError(bool success)
{
    if (!success) return Error<std::string>("Error");
    return Success<void>();
}

Result<int, void>SuccessOrErrorWithoutValue(bool success)
{
    if (!success) return Error<void>();
    return Success<int>(21000000);
}

BOOST_AUTO_TEST_CASE(result_type_tests)
{
    {
        Result<int, std::string> result = SuccessOrErrorValue(true);
        BOOST_CHECK_EQUAL(result.success, true);
        BOOST_CHECK_EQUAL(result.success_value, 21000000);
    }

    {
        Result<int, std::string> result = SuccessOrErrorValue(false);
        BOOST_CHECK_EQUAL(result.success, false);
        BOOST_CHECK_EQUAL(result.error_value, "Error");
    }

    {
        Result<void, std::string> result = SuccessWithoutValueOrError(true);
        BOOST_CHECK_EQUAL(result.success, true);
    }

    {
        Result<void, std::string> result = SuccessWithoutValueOrError(false);
        BOOST_CHECK_EQUAL(result.success, false);
        BOOST_CHECK_EQUAL(result.error_value, "Error");
    }

    {
        Result<int, void> result = SuccessOrErrorWithoutValue(true);
        BOOST_CHECK_EQUAL(result.success, true);
        BOOST_CHECK_EQUAL(result.success_value, 21000000);
    }

    {
        Result<int, void> result = SuccessOrErrorWithoutValue(false);
        BOOST_CHECK_EQUAL(result.success, false);
    }

}
BOOST_AUTO_TEST_SUITE_END()
