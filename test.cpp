

#include <iostream>
#include <unistd.h>
#include <cassert>
#include <random>
#include <array>
#include <thread>
#include <chrono>

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

         for (int& num : result) {
             num = rand() % 2;
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

         std::array<int, 5> zero_array = {0,0,0,0,0};
         std::array<int, 5> result_array;
         result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
         result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
         result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
         result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
         result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);
         return (result_array == zero_array);

}

bool verify_simple_setter_getter() {

         for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

                  bool print_enable = false;

                  std::array<int, 5> array = generate_5_array();;
                  std::array<int, 5> result_array;

                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
                  if(print_enable) std::cout << "Im setting " << array << " for the verify_simple_setter_getter_test" << std::endl;
                  
                  long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                  if(print_enable) std::cout << "SysCall  SET_SEC returned: " << returned << std::endl;

                  if(returned < 0) return 0;

                  result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
                  result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
                  result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
                  result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
                  result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);

                  if(print_enable) std::cout << "I got " << array << " for the verify_simple_setter_getter_test" << std::endl;

                  if(result_array != array) return 0;

                  if(print_enable) std::cout << "verify_simple_setter_getter_test Passed for the " << i << "time" << std::endl;
                  if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
                  return 1;
         }

}


int main() {

         srand(static_cast<unsigned int>(time(0))); // Seed for randomization

         run_test("Default clearance is zero", verify_default_is_zero_test);
         run_test("Simple Setter Getter test", verify_simple_setter_getter);

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