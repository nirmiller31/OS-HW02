

#include <iostream>
#include <unistd.h>
#include <cassert>
#include <errno.h>
#include <random>
#include <array>
#include <thread>
#include <chrono>
#include <sys/types.h>
#include <sys/wait.h>

#define LETTER_S_SWORD              's'
#define LETTER_M_MIDNIGHT           'm'
#define LETTER_C_CLAMP              'c'
#define LETTER_D_DUTY               'd'
#define LETTER_I_ISOLATE            'i'

#define FIRST_FUNC_SET_SEC          334
#define SECOND_FUNC_GET_SEC         335
#define THIRD_FUNC_CHECK_SEC        336
#define FOURTH_FUNC_FLIP_SEC_BRANCH 337

#define SHORT_TEST_ITERATIONS       20
#define MEDIUM_TEST_ITERATIONS      70
#define LONG_TEST_ITERATIONS        120

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
         os << "[";
         for (std::size_t i = 0; i < N; ++i) {
                  os << arr[i];
                  if (i < N - 1) os << ", ";
         }
         os << "]";
         return os;
}

std::array<int, 5> generate_5_array() {                                                            // Generate binary array
         std::array<int, 5> result;
         for (int& num : result) {num = rand() % 2;}
         return result;
}

std::array<int, 5> generate_non_binary_5_array() {                                                  // Generate array

         std::array<int, 5> result;
         for (int& num : result) {
             num = rand() / 7;
             if(num % 3 == 0) {num=0;}
         }
         return result;
}

std::array<int, 5> generate_neagtive_positive_5_array() {                                          // Generate array with no limits

         std::array<int, 5> result;
         int negative_index = rand() % 5;
         for(int i=0 ; i<5 ; i++){
                  result[i] = rand() / 7;
                  if(result[i] % 3 == 0 && i != negative_index) {result[i]=0;}
                  if(result[i] % 5 == 0 || i == negative_index) {result[i]*=(-1);}
         }
         return result;
}

using TestFunc = bool(*)();                                                                        // Simple test type

std::vector<std::string> failed_tests;                                                             // Stores failed test names

void run_test(const std::string& name, TestFunc func) {                                            // Runs a single test and logs the result
    bool passed = func();
    if (passed) {
        std::cout << "[PASS] " << name << "\n";
    } else {
        std::cout << "[FAIL] " << name << "\n";
        failed_tests.push_back(name);
    }
}

// ===================================================================================================================================================
// =============================================================== TESTS FROM HERE ===================================================================

bool verify_default_is_zero_test() {

         bool print_enable = false;

         std::array<int, 5> zero_array = {0,0,0,0,0};
         std::array<int, 5> result_array;

         // Get the clearance using system call
         result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
         result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
         result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
         result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
         result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);
         if(print_enable) std::cout << "I got " << result_array << " for the verify_default_is_zero_test" << std::endl;
         return (result_array == zero_array);
}

bool verify_simple_setter_getter_test() {

         for(int i=0 ; i<MEDIUM_TEST_ITERATIONS ; i++) {

                  bool print_enable = false;

                  std::array<int, 5> array = generate_5_array();;
                  std::array<int, 5> result_array;

                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_simple_setter_getter_test" << std::endl;
                  
                  // Set the clearance according to the array
                  long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << " 0 is GOOD!" << std::endl;

                  if(returned < 0) {return 0; }

                  // Get the clearance using system call
                  result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
                  result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
                  result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
                  result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
                  result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);

                  if(print_enable) std::cout << "I got " << array << " for the verify_simple_setter_getter_test" << std::endl;

                  if(result_array != array) {return 0; }

                  if(print_enable) std::cout << "verify_simple_setter_getter_test Passed for the " << i+1 << " time" << std::endl;
                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;        
         }
         return true;
}

bool verify_non_binary_setter_getter_test() {

         for(int i=0 ; i<MEDIUM_TEST_ITERATIONS ; i++) {

                  bool print_enable = false;

                  std::array<int, 5> array = generate_non_binary_5_array();;
                  std::array<int, 5> result_array;

                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_non_binary_setter_getter_test" << std::endl;
                  
                  // Set the clearance according to the array
                  long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << " 0 is GOOD!" << std::endl;

                  if(returned < 0) {return false; }

                  // Get the clearance using system call
                  result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
                  result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
                  result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
                  result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
                  result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);

                  if(print_enable) std::cout << "I got " << result_array << " for the verify_non_binary_setter_getter_test" << std::endl;

                  // Norm the resaults (0 - >0, <num> -> 1)
                  array[0] = (array[0] > 0);
                  array[1] = (array[1] > 0);
                  array[2] = (array[2] > 0);
                  array[3] = (array[3] > 0);
                  array[4] = (array[4] > 0);

                  if(print_enable) std::cout << "I got " << array << " for the verify_non_binary_setter_getter_test" << std::endl;

                  if(result_array != array) {return false; }

                  if(print_enable) std::cout << "verify_non_binary_setter_getter_test Passed for the " << i+1 << " time" << std::endl;
                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;        
         }
         return true;
}

bool verify_wide_fork_setter_getter_test() {

         for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

                  bool print_enable = false;

                  std::array<int, 5> array = generate_5_array();;
                  std::array<int, 5> result_array;
                  std::array<int, 5> child_result_array;

                  if(print_enable) std::cout << "----------------------------------------------------------------------" << std::endl;
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_wide_fork_setter_getter_test" << std::endl;
                  
                  long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(print_enable) std::cout << "SysCall  SET_SEC returned: " << returned << std::endl;

                  if(returned < 0) return false;

                  for(int j=0 ; j<MEDIUM_TEST_ITERATIONS ; j++){
                           
                           pid_t pid = fork();                 // Fork to verify we inherit the clearance field

                           if(pid == 0) {                      // Child process, verify the clearance field is as written
                                    child_result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
                                    child_result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
                                    child_result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
                                    child_result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
                                    child_result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);
                                    if(print_enable) std::cout << "I got " << child_result_array << " for the verify_wide_fork_setter_getter_test" << std::endl;
                                    if(child_result_array != array) _exit(1);             // FAIL
                                    _exit(0);                                             // SUCCESS
                           }
                           if(pid > 0) {                       // Parent process, just wait the child
                                    int status;
                                    waitpid(pid, &status, 0);
                                    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {return false; }
                                    if(print_enable) std::cout << "Just Verified " << pid << " 's clearance field" << std::endl;
                           }
                           if(pid < 0) {
                                    if(print_enable) std::cout << "Unexpected ERROR, verify_wide_fork_setter_getter_test failed" << std::endl;
                                    return false;                  // Fork failed
                           }
                  }

                  if(print_enable) std::cout << "verify_wide_fork_setter_getter_test Passed for the " << i+1 << " time" << std::endl;
                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
                  
         }
         return true;
}


void recursive_fork(std::array<int, 5> grand_parent_array, bool print_enable, int current_deep){

         if(print_enable) std::cout << "verify_deep_fork_setter_getter_test Im " << current_deep << " deep in the recursive fork" << std::endl;

         std::array<int, 5> child_result_array;

         pid_t pid = fork();

         if(pid < 0) {
                  if(print_enable) std::cout << "Unexpected ERROR, verify_wide_fork_setter_getter_test failed" << std::endl;
                  _exit(1);                  // Fork failed
         }
         else if(pid == 0) {                      // Child process, verify the clearance field is as written

                  child_result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
                  child_result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
                  child_result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
                  child_result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
                  child_result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);
                  if(print_enable) std::cout << "I got " << child_result_array << " for the verify_wide_fork_setter_getter_test" << std::endl;
                  if(child_result_array != grand_parent_array) _exit(1);           // FAIL
                  if(current_deep < SHORT_TEST_ITERATIONS){                        // Move on deeper
                           recursive_fork(grand_parent_array, print_enable, current_deep + 1);   
                  }
                   _exit(0);                                                     // SUCCESS   
         }
         else if(pid > 0) {                       // Parent process, just wait the child
                  int status;
                  waitpid(pid, &status, 0);
                  if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {_exit(1); }
                  if(print_enable) std::cout << "Just Verified pid " << pid << "'s clearance field" << std::endl;
                  _exit(0);
         }

}


bool verify_deep_fork_setter_getter_test() {

         for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

                  bool print_enable = false;

                  std::array<int, 5> array = generate_5_array();
                  std::array<int, 5> child_result_array;

                  if(print_enable) std::cout << "----------------------------------------------------------------------" << std::endl;
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_deep_fork_setter_getter_test" << std::endl;
                  
                  long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;
                  if(returned < 0) return false;
                           
                  pid_t pid = fork();                 // Fork to verify we inherit the clearance field

                  if(pid < 0) {
                           if(print_enable) std::cout << "Unexpected ERROR, verify_deep_fork_setter_getter_test failed" << std::endl;
                           return false;                  // Fork failed
                  }
                  else if(pid == 0) {                      // Child process, verify the clearance field is as written
                           child_result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
                           child_result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
                           child_result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
                           child_result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
                           child_result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);
                           if(print_enable) std::cout << "I got " << child_result_array << " for the verify_deep_fork_setter_getter_test" << std::endl;
                           if(child_result_array != array) _exit(1);             // FAIL
                           
                           recursive_fork(array, print_enable, 1);               // Move on deeper
                           _exit(0);                                             // SUCCESS
                  }
                  else if(pid > 0) {                       // Parent process, just wait the child
                           int status;
                           waitpid(pid, &status, 0);
                           if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {return false; }
                           if(print_enable) std::cout << "Just Verified " << pid << " 's clearance field" << std::endl;
                  }
                  
                  if(print_enable) std::cout << "verify_deep_fork_setter_getter_test Passed for the " << i+1 << " time" << std::endl;
                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
                  
         }
         return true;
}

bool verify_simple_check_sec_test() {

         for(int i=0 ; i<MEDIUM_TEST_ITERATIONS ; i++) {

                  bool print_enable = false;

                  std::array<int, 5> array = generate_5_array();;
                  std::array<int, 5> result_array;

                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_simple_check_sec_test" << std::endl;
                  
                  // Set the clearance according to the array
                  long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << " 0 is GOOD!" << std::endl;

                  if(returned < 0) {return 0; }

                  pid_t pid = getpid();

                  // Get the clearance using check_sec system call to its pid
                  result_array[0] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
                  result_array[1] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
                  result_array[2] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
                  result_array[3] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
                  result_array[4] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);

                  if(print_enable) std::cout << "I got " << array << " for the verify_simple_check_sec_test" << std::endl;

                  if(result_array != array) {return 0; }

                  if(print_enable) std::cout << "verify_simple_check_sec_test Passed for the " << i+1 << " time" << std::endl;
                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;        
         }
         return true;
}

bool verify_non_binary_check_sec_test() {

         for(int i=0 ; i<MEDIUM_TEST_ITERATIONS ; i++) {

                  bool print_enable = false;

                  std::array<int, 5> array = generate_non_binary_5_array();;
                  std::array<int, 5> result_array;

                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_non_binary_check_sec_test" << std::endl;
                  
                  // Set the clearance according to the array
                  long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << " 0 is GOOD!" << std::endl;

                  if(returned < 0) {return false; }

                  pid_t pid = getpid();

                  // Get the clearance using check_sec system call to its pid
                  result_array[0] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
                  result_array[1] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
                  result_array[2] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
                  result_array[3] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
                  result_array[4] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);

                  if(print_enable) std::cout << "I got " << result_array << " for the verify_non_binary_check_sec_test" << std::endl;

                  // Norm the resaults (0 - >0, <num> -> 1)
                  array[0] = (array[0] > 0);
                  array[1] = (array[1] > 0);
                  array[2] = (array[2] > 0);
                  array[3] = (array[3] > 0);
                  array[4] = (array[4] > 0);

                  if(print_enable) std::cout << "I got " << array << " for the verify_non_binary_check_sec_test" << std::endl;

                  if(result_array != array) {return false; }

                  if(print_enable) std::cout << "verify_non_binary_check_sec_test Passed for the " << i+1 << " time" << std::endl;
                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;        
         }
         return true;
}

bool verify_first_function_error_test() {

         if (seteuid(0) == -1) {                                                                                                                // Verify we run with root previllages
                  std::cout << "Error test failed, Please run command with sudo: ./test" << std::endl;
                  return false;
         }

         for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

                  bool print_enable = false;
                  if(print_enable) std::cout << "----------------------------------------------------------------------" << std::endl;

                  // Try to insert negative clearances, expect -1 and errno == EINVAL
                  std::array<int, 5> array = generate_neagtive_positive_5_array();
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_first_function_error_test" << std::endl;
                  long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;
                  if((returned != -1) || (errno != EINVAL)) return false;
                  if(print_enable) std::cout << "Just verified case of negative values to SET_SEC, got expected result: " << returned << std::endl;

                  // Try to insert normal clearances, without root privillage expect -1 and errno == EPERM
                  array = generate_5_array();
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_first_function_error_test" << std::endl;
                  if(seteuid(1000) == -1) {return false;}
                  returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;
                  if(returned != -1) return false;
                  if(errno != EPERM) return false;
                  if(print_enable) std::cout << "Just verified lack of root previllages to SET_SEC, got expected result" << returned << std::endl;

                  // Try to insert negative clearances, without root privillage expect -1 and errno == EINVAL
                  array = generate_neagtive_positive_5_array();
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_first_function_error_test with no root privillages" << std::endl;
                  returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if((returned != -1) || (errno != EINVAL)) return false;
                  if(print_enable) std::cout << "Just verified case of negative values with no root prev. to SET_SEC, got expected result: " << returned << std::endl;

                  if (seteuid(0) == -1) {return false;}

                  // Try to insert normal clearances, with root privillage expect 0 (Success)
                  array = generate_5_array();
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_first_function_error_test" << std::endl;
                  if(print_enable) std::cout << "effective uid " << geteuid() << std::endl;
                  returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(returned != 0) return false;

                  if(print_enable) std::cout << "verify_first_function_error_test Passed for the " << i+1 << "time" << std::endl;
                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
         }
         return true;
}


bool verify_second_function_error_test() {

         if (seteuid(0) == -1) {                                                                                                                // Verify we run with root previllages
                  std::cout << "Error test failed, Please run command with sudo: ./test" << std::endl;
                  return 0;
         }

         for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

                  bool print_enable = false;

                  if(print_enable) std::cout << "----------------------------------------------------------------------" << std::endl;

                  // Try to insert negative clearances, expect -1 and errno == EINVAL
                  std::array<char, 21> letters = {
                           'a', 'b', 'e', 'f', 'g', 'h',
                           'j', 'k', 'l', 'n', 'o', 'p',
                           'q', 'r', 't', 'u', 'v', 'w',
                           'x', 'y', 'z'
                       };
                  int letter_index = rand() % 21;
                  char invalid_character = letters[letter_index];
                  if(print_enable) std::cout << "Im setting letter: " << invalid_character << " for the verify_second_function_error_test" << std::endl;
                  long returned = syscall(SECOND_FUNC_GET_SEC, invalid_character);
                  if(print_enable) std::cout << "SysCall GET_SEC returned: " << returned << std::endl;

                  if((returned != -1) || (errno != EINVAL)) return false;
                  if(print_enable) std::cout << "Just verified case of negative values to GET_SEC, got expected result" << returned << std::endl;
                  if(print_enable) std::cout << "verify_second_function_error_test Passed for the " << i+1 << " time" << std::endl;
                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
         }
         return true;
}


int main() {

         srand(static_cast<unsigned int>(time(0))); // Seed for randomization

         run_test("Default clearance is zero", verify_default_is_zero_test);
         run_test("Simple Setter Getter test", verify_simple_setter_getter_test);
         run_test("Non Binary Setter Getter test", verify_non_binary_setter_getter_test);
         run_test("Wide Fork Setter Getter test", verify_wide_fork_setter_getter_test);
         run_test("Deep Fork Setter Getter test", verify_deep_fork_setter_getter_test);
         run_test("First function error test", verify_first_function_error_test);
         run_test("Second function error test", verify_second_function_error_test);
         run_test("Simple check_sec test", verify_simple_check_sec_test);
         run_test("Non binary check_sec test", verify_non_binary_check_sec_test);
         

         std::cout << "\nTest Summary:\n";                                                         // Summary
         if (failed_tests.empty()) {
                  std::cout << "All tests passed.\n";
         }
         else {
                  std::cout << failed_tests.size() << " test(s) failed:\n";
                  for (const std::string& name : failed_tests) {
                           std::cout << " - " << name << "\n";
                  }
         }

         return 0;

}