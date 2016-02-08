project(cpp-test)

include(lambda/CMakeLists.txt)
include(operator_overload/CMakeLists.txt)
include(virtual_table/CMakeLists.txt)

add_executable(lambda ${lambda_test_src})
add_executable(operator_overload ${operator_overload_test_src})
add_executable(virtual_table ${virtual_table_test_src})