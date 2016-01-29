project(cpp-test)

set(
vptrtest_srcs
	vptrtest/main.cpp
)

add_executable(vptrtest ${vptrtest_srcs})

set(
operator_test_srcs
	operator_test/Fraction.cpp
	operator_test/Fraction.h
	operator_test/main.cpp
)
include_directories(operator_test)
add_executable(operator_test ${operator_test_srcs})