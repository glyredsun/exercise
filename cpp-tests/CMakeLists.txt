project(cpp-test)

set(
virtual_table_srcs
	virtual_table/main.cpp
)
add_executable(virtual_table ${virtual_table_srcs})

set(
operator_overload_srcs
	operator_overload/Fraction.cpp
	operator_overload/Fraction.h
	operator_overload/main.cpp
)
include_directories(operator_overload)
add_executable(operator_overload ${operator_overload_srcs})