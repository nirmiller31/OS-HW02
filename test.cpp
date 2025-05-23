

#include <iostream>
#include <unistd.h>
#include <cassert>
#include <errno.h>
#include <random>
#include <array>
#include <thread>
#include <chrono>
#include <signal.h>
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

        for(int i=0 ; i<MEDIUM_TEST_ITERATIONS ; i++) {
            // Get the clearance using system call
            result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
            result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
            result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
            result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
            result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);
            if(print_enable) std::cout << "I got " << result_array << " for the verify_default_is_zero_test" << std::endl;
            if(result_array != zero_array) {
                std::cout << "Please run this test afyet reseting your VM, the course's test put 1 in init's clearance" << std::endl;
                return false;}
        }
        return true;
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

            if(print_enable) std::cout << "I got " << result_array << " for the verify_simple_check_sec_test" << std::endl;

            for(int i = 0 ; i<5 ; i++) {
            if(result_array[i] && array[i]) continue;
            else if (result_array[i] == -1 && array[i] == 0) continue;
            else return false;
            }

            if(print_enable) std::cout << "verify_simple_check_sec_test Passed for the " << i+1 << " time" << std::endl;
            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;        
        }
        return true;
    }

    bool verify_init_check_sec_test() {

        for(int i=0 ; i<MEDIUM_TEST_ITERATIONS ; i++) {

            bool print_enable = false;

            std::array<int, 5> array_of_ones = {1,1,1,1,1};
            std::array<int, 5> array_of_zeros = {0,0,0,0,0};
            std::array<int, 5> result_array;

            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
            if(print_enable) std::cout << "Im setting " << array_of_ones << " for the verify_init_check_sec_test" << std::endl;
            
            // Set the maximum clearance in order to access
            long returned = syscall(FIRST_FUNC_SET_SEC, array_of_ones[0], array_of_ones[1], array_of_ones[2], array_of_ones[3], array_of_ones[4]);
            if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << " 0 is GOOD!" << std::endl;

            if(returned < 0) {return 0; }

            pid_t pid = 1;

            // Get the clearance of init using system call, we expect 0's
            result_array[0] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
            result_array[1] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
            result_array[2] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
            result_array[3] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
            result_array[4] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);

            if(print_enable) std::cout << "I got " << result_array << " for the verify_init_check_sec_test" << std::endl;

            if(result_array != array_of_zeros) {return false;}

            if(print_enable) std::cout << "verify_init_check_sec_test Passed for the " << i+1 << " time" << std::endl;
            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;        
        }
        return true;
    }

    bool verify_non_binary_check_sec_test() {

        for(int i=0 ; i<MEDIUM_TEST_ITERATIONS ; i++) {

            bool print_enable = false;

            std::array<int, 5> array = generate_non_binary_5_array();
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

            for(int i = 0 ; i<5 ; i++) {
            if(result_array[i] && array[i]) continue;
            else if (result_array[i] == -1 && array[i] == 0) continue;
            else return false;
            }

            if(print_enable) std::cout << "verify_non_binary_check_sec_test Passed for the " << i+1 << " time" << std::endl;
            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;        
        }
        return true;
    }


    bool verify_simple_fork_check_sec_test() {

        for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

            bool print_enable = false;

            std::array<int, 5> result_array;
            std::array<int, 5> child_result_array;

            if(print_enable) std::cout << "----------------------------------------------------------------------" << std::endl;

            for(int j=0 ; j<MEDIUM_TEST_ITERATIONS ; j++){

                std::array<int, 5> array = generate_5_array();
                if(print_enable) std::cout << "Im setting " << array << " for the verify_simple_fork_check_sec_test" << std::endl;
                long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;
                if(returned < 0) return false;
                
                pid_t pid = fork();                 // Fork to verify we inherit the clearance field

                if(pid == 0) {                      // Child process, should inherit the clearance field
                        pause();                   // Wait for the kill
                }
                if(pid > 0) {                       // Parent process

                    std::array<int, 5> array_of_ones = {1,1,1,1,1};
                    returned = syscall(FIRST_FUNC_SET_SEC, array_of_ones[0], array_of_ones[1], array_of_ones[2], array_of_ones[3], array_of_ones[4]);               // Let the caller have all the clerances, error handling checked seperatly
                    if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;

                    if(returned < 0) return false;
                    // Get the clearance using the pid and third sys_call
                    child_result_array[0] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
                    child_result_array[1] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
                    child_result_array[2] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
                    child_result_array[3] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
                    child_result_array[4] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);

                    kill(pid, SIGKILL);        // Kill child
                    waitpid(pid, nullptr, 0);  // Reap zombie

                    if(print_enable) std::cout << "I got " << child_result_array << " for the verify_simple_fork_check_sec_test" << std::endl;
                    if(child_result_array != array) {return false;}
                    if(print_enable) std::cout << "Just Verified " << pid << " 's clearance field" << std::endl;
                }
                if(pid < 0) {
                    if(print_enable) std::cout << "Unexpected ERROR, verify_simple_fork_check_sec_test failed" << std::endl;
                    return false;              // Fork failed
                }
            }

            if(print_enable) std::cout << "verify_simple_fork_check_sec_test Passed for the " << i+1 << " time" << std::endl;
            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
                
        }
        return true;
    }

    bool verify_dynamic_fork_check_sec_test() {

        for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

            bool print_enable = false;

            std::array<int, 5> result_array;
            std::array<int, 5> child_result_array;

            if(print_enable) std::cout << "----------------------------------------------------------------------" << std::endl;

            for(int j=0 ; j<MEDIUM_TEST_ITERATIONS ; j++){

                std::array<int, 5> array = generate_5_array();
                if(print_enable) std::cout << "Im setting " << array << " for the verify_dynamic_fork_check_sec_test" << std::endl;
                long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
                if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;
                if(returned < 0) return false;

                std::array<int, 5> new_array = generate_5_array();        // To be updated in the child
                
                int pipefd[2];
                if(pipe(pipefd) == -1) {return false;}

                pid_t pid = fork();                 // Fork to verify we inherit the clearance field

                if(pid == 0) {                      // Child process, should inherit the clearance field
                    close(pipefd[0]); // pipe_shit

                    if(print_enable) std::cout << "Im setting " << new_array << " to the child in verify_dynamic_fork_check_sec_test" << std::endl;
                    returned = syscall(FIRST_FUNC_SET_SEC, new_array[0], new_array[1], new_array[2], new_array[3], new_array[4]);

                    write(pipefd[1], "1", 1); // pipe_shit to annanuce the clearance field had been written
                    close(pipefd[1]); // pipe_shit
                    pause();                   // Wait for the kill
                }
                if(pid > 0) {                       // Parent process
                    close(pipefd[1]); // pipe_shit

                    std::array<int, 5> array_of_ones = {1,1,1,1,1};
                    returned = syscall(FIRST_FUNC_SET_SEC, array_of_ones[0], array_of_ones[1], array_of_ones[2], array_of_ones[3], array_of_ones[4]);               // Let the caller have all the clerances, error handling checked seperatly
                    if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;
                    if(returned < 0) return false;

                    char buffer; // pipe_shit
                    read(pipefd[0], &buffer, 1); // Wait for child to finish the checkpoint
                    close(pipefd[0]);

                    // Get the clearance using the pid and third sys_call
                    child_result_array[0] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
                    child_result_array[1] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
                    child_result_array[2] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
                    child_result_array[3] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
                    child_result_array[4] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);

                    kill(pid, SIGKILL);        // Kill child
                    waitpid(pid, nullptr, 0);  // Reap zombie

                    if(print_enable) std::cout << "I got " << child_result_array << " for the verify_dynamic_fork_check_sec_test" << std::endl;
                    if(child_result_array != new_array) {return false;}
                    if(print_enable) std::cout << "Just Verified " << pid << " 's clearance field" << std::endl;
                }
                if(pid < 0) {
                    if(print_enable) std::cout << "Unexpected ERROR, verify_dynamic_fork_check_sec_test failed" << std::endl;
                    return false;              // Fork failed
                }
            }
            if(print_enable) std::cout << "verify_dynamic_fork_check_sec_test Passed for the " << i+1 << " time" << std::endl;
            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;           
        }
        return true;
    }

    bool verify_simple_init_flip_sec_branch_test() {

        for(int i=0 ; i<MEDIUM_TEST_ITERATIONS ; i++) {

            bool print_enable = false;

            std::array<int, 5> array_of_ones = {1,1,1,1,1};
            std::array<int, 5> result_array;
            std::array<int, 5> init_array;
            std::array<int, 5> inverted_init_array;

            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
            if(print_enable) std::cout << "Im setting " << array_of_ones << " for the verify_simple_init_flip_sec_branch_test" << std::endl;
            
            // Set array of ones to have full access
            long returned = syscall(FIRST_FUNC_SET_SEC, array_of_ones[0], array_of_ones[1], array_of_ones[2], array_of_ones[3], array_of_ones[4]);
            if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << " 0 is GOOD!" << std::endl;
            if(returned < 0) {return 0; }

            pid_t pid = 1;

            // Get the clearance of init using pid == 1
            init_array[0] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
            init_array[1] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
            init_array[2] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
            init_array[3] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
            init_array[4] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);

            if(print_enable) std::cout << "I got init array: " << init_array << " for the verify_init_check_sec_test" << std::endl;

            inverted_init_array[0] = init_array[0] ^ 1;
            inverted_init_array[1] = init_array[1] ^ 1;
            inverted_init_array[2] = init_array[2] ^ 1;
            inverted_init_array[3] = init_array[3] ^ 1;
            inverted_init_array[4] = init_array[4] ^ 1;

            if(print_enable) std::cout << "I got inverted init array: " << inverted_init_array << " for the verify_init_check_sec_test" << std::endl;

            int supposed_init_height = 5000;
            // We expect to flip all inits from 0 to 1
            if(print_enable) std::cout << "Im flipping the init's clearance from 0 to 1 for the verify_simple_init_flip_sec_branch_test" << std::endl;
            result_array[0] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_S_SWORD);
            result_array[1] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_M_MIDNIGHT);
            result_array[2] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_C_CLAMP);
            result_array[3] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_D_DUTY);
            result_array[4] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_I_ISOLATE);

            // Get the clearance of init using system call, we expect 0's
            result_array[0] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
            result_array[1] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
            result_array[2] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
            result_array[3] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
            result_array[4] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);
            if(print_enable) std::cout << "I got " << result_array << " for the verify_simple_init_flip_sec_branch_test" << std::endl;

            if(result_array != inverted_init_array){ return false;}

            if(print_enable) std::cout << "Im flipping the init's clearance from 1 to 0 for the verify_simple_init_flip_sec_branch_test" << std::endl;
            result_array[0] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_S_SWORD);
            result_array[1] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_M_MIDNIGHT);
            result_array[2] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_C_CLAMP);
            result_array[3] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_D_DUTY);
            result_array[4] = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, supposed_init_height, LETTER_I_ISOLATE);

            result_array[0] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
            result_array[1] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
            result_array[2] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
            result_array[3] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
            result_array[4] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);
            if(print_enable) std::cout << "I got " << result_array << " for the verify_simple_init_flip_sec_branch_test" << std::endl;

            if(result_array != init_array){ return false;}

            if(print_enable) std::cout << "verify_simple_init_flip_sec_branch_test Passed for the " << i+1 << " time" << std::endl;
            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;        
        }
        return true;
    }
    
void recursive_branch_fork(int pipe_write_fd, int return_pipe_fd, bool print_enable, int current_deep, int max_depth, int flipped_clearance_index) {
    std::array<char, 5> letters_decode = {
        LETTER_S_SWORD,
        LETTER_M_MIDNIGHT,
        LETTER_C_CLAMP,
        LETTER_D_DUTY,
        LETTER_I_ISOLATE
    };

    if (print_enable) std::cout << "verify_deep_fork_setter_getter_test Im " << current_deep << " deep in the recursive fork, out of: " << max_depth << std::endl;

    std::array<int, 5> array = generate_5_array();

    if (current_deep < max_depth) {
        if (print_enable) std::cout << "Setting clearance at depth " << current_deep << ": " << array << std::endl;
        long returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
        if (print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;
        if (returned < 0) _exit(1);

        int pipefd[2];
        pipe(pipefd);

        pid_t pid = fork();

        if (pid < 0) {
            if (print_enable) std::cout << "Fork failed\n";
            _exit(1);
        } else if (pid == 0) {          // countinue the recursion
            close(pipefd[0]);
            recursive_branch_fork(pipefd[1], return_pipe_fd, print_enable, current_deep + 1, max_depth, flipped_clearance_index);
        } else {
            close(pipefd[1]);           // local parent process

            std::array<int, 6> buf;
            while (read(pipefd[0], buf.data(), sizeof(buf)) == sizeof(buf))
                write(pipe_write_fd, buf.data(), sizeof(buf));
            close(pipefd[0]);

            std::array<int, 6> combined;
            for (int i = 0; i < 5; ++i) combined[i] = array[i];
            combined[5] = getpid();
            write(pipe_write_fd, combined.data(), sizeof(combined));
        }
    } else {                                                        // End of the branch (bottom), call the flip and do the flip, send with pipes the functions' returned value
        syscall(FIRST_FUNC_SET_SEC, 1,1,1,1,1);
        long returned = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, max_depth, letters_decode[flipped_clearance_index]);
        if (print_enable) std::cout << "SysCall FLIP_SEC_BRANCH returned: " << returned << std::endl;
        if (print_enable && returned == -1) std::cout << "SysCall FLIP_SEC_BRANCH errno: " << errno << std::endl;
        if (returned < 0) _exit(1);

        write(return_pipe_fd, &returned, sizeof(returned));
        close(return_pipe_fd);
    }

    close(pipe_write_fd);
}

bool verify_flip_sec_branch_test() {
    std::array<char, 5> letters_decode = {
        LETTER_S_SWORD,
        LETTER_M_MIDNIGHT,
        LETTER_C_CLAMP,
        LETTER_D_DUTY,
        LETTER_I_ISOLATE
    };

    for (int i = 0; i < SHORT_TEST_ITERATIONS; ++i) {
        bool print_enable = false;

        std::vector<std::array<int, 6>> result_data;
        std::vector<std::array<int, 6>> expected_data;
        std::array<int, 5> result_array;
        std::array<int, 6> recursion_array;

        int recursion_deep = (rand() % SHORT_TEST_ITERATIONS) + 1;
        int flipped_clearance_index = rand() % 5;

        std::array<int, 5> root_array = generate_5_array();         // To be a parent, there has to be a parent, height is >= 1
        if (print_enable) std::cout << "Setting clearance at depth 0: " << root_array << std::endl;
        long returned = syscall(FIRST_FUNC_SET_SEC, root_array[0], root_array[1], root_array[2], root_array[3], root_array[4]);
        if (print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;
        if (returned < 0) return false;

        int pipefd[2];  // pipe_hit
        pipe(pipefd);

        int return_pipefd[2];  // pipe_hit
        pipe(return_pipefd);

        pid_t pid = fork();

        if (pid < 0) return false;
        else if (pid == 0) {
            close(pipefd[0]);  // pipe_hit
            close(return_pipefd[0]);  // pipe_hit
            returned = syscall(FIRST_FUNC_SET_SEC, root_array[0], root_array[1], root_array[2], root_array[3], root_array[4]);
            if (returned < 0) _exit(1);
            recursive_branch_fork(pipefd[1], return_pipefd[1], print_enable, 1, recursion_deep, flipped_clearance_index);
            pause();
        } else {
            close(pipefd[1]);
            close(return_pipefd[1]);

            int status;
            waitpid(pid, &status, WNOHANG);

            std::array<int, 6> buf;
            while (read(pipefd[0], buf.data(), sizeof(buf)) == sizeof(buf))
                result_data.push_back(buf);
            close(pipefd[0]);

            long returned_from_flip;
            read(return_pipefd[0], &returned_from_flip, sizeof(returned_from_flip));
            close(return_pipefd[0]);

            int our_final_count = 0;
            for (auto &arr : result_data) {
                arr[flipped_clearance_index] ^= 1;
                if (arr[flipped_clearance_index]) our_final_count++;
                expected_data.push_back(arr);
                // std::cout << " the desiredd vector: " << arr << std::endl;
            }

            std::array<int, 6> root_combined;
            for (int i = 0; i < 5; ++i) root_combined[i] = root_array[i];
            root_combined[flipped_clearance_index] ^= 1;
            if (root_combined[flipped_clearance_index]) our_final_count++;
            root_combined[5] = getpid();
            expected_data.push_back(root_combined);

            // Get parents actual fields and compare to what we wrote&flipped:
            result_array[0] = syscall(SECOND_FUNC_GET_SEC, LETTER_S_SWORD);
            result_array[1] = syscall(SECOND_FUNC_GET_SEC, LETTER_M_MIDNIGHT);
            result_array[2] = syscall(SECOND_FUNC_GET_SEC, LETTER_C_CLAMP);
            result_array[3] = syscall(SECOND_FUNC_GET_SEC, LETTER_D_DUTY);
            result_array[4] = syscall(SECOND_FUNC_GET_SEC, LETTER_I_ISOLATE);
            for(int i=0 ; i<5 ; i++){
                if(result_array[i] != root_combined[i]) return false;
                if (print_enable) std::cout << " vector: " << result_array[i] << ", pid: " << root_combined[5] << std::endl;
            }
            syscall(FIRST_FUNC_SET_SEC, 1,1,1,1,1);     // Set all clearances to get others', after verified

            for (int i=0 ; i<recursion_deep-1 ; i++) {

                pid_t(pid) = expected_data[i][5];

                if (print_enable) std::cout << " vector: " << expected_data[i] << ", pid: " << expected_data[i][5] << std::endl;
                result_array[0] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
                result_array[1] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
                result_array[2] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
                result_array[3] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
                result_array[4] = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);
                if (print_enable) std::cout << " errno: " << errno<< std::endl;

                for(int j=0 ; j<5 ; j++){
                    if (print_enable) std::cout << " vector: " << result_array[j] << ", pid: " << expected_data[i][5] << std::endl;
                    if(result_array[j] != expected_data[i][j]) return false;
                }
            }
            if (print_enable) std::cout << "Flipped: " << flipped_clearance_index << " bit, which is: " << char(letters_decode[flipped_clearance_index]) << std::endl;
            if (print_enable) std::cout << "The actual returned value from FLIP_SEC_BRANCH: " << returned_from_flip << std::endl;
            if (print_enable) std::cout << "Our final count (based on the returned array): " << our_final_count << std::endl;
            if(our_final_count != returned_from_flip) return false;
        }
    }

    return true;
}

    bool verify_first_function_error_handling_test() {

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


    bool verify_second_function_error_handling_test() {

        if (seteuid(0) == -1) {                                                                                                                // Verify we run with root previllages
            std::cout << "Error test failed, Please run command with sudo: ./test" << std::endl;
            return 0;
        }

        for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

            bool print_enable = false;

            if(print_enable) std::cout << "----------------------------------------------------------------------" << std::endl;

            // Try to insert wrong clearances, expect -1 and errno == EINVAL
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
            if(print_enable) std::cout << "Just verified case of wrong values to GET_SEC, got expected result" << returned << std::endl;
            if(print_enable) std::cout << "verify_second_function_error_test Passed for the " << i+1 << " time" << std::endl;
            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
        }
        return true;
    }

    bool verify_third_function_error_handling_test() {

        if (seteuid(0) == -1) {                                                                                                                // Verify we run with root previllages
            std::cout << "Error test failed, Please run command with sudo: ./test" << std::endl;
            return 0;
        }

        for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

            bool print_enable = false;

            if(print_enable) std::cout << "----------------------------------------------------------------------" << std::endl;

            std::array<char, 5> letters_decode = {
                    LETTER_S_SWORD,
                    LETTER_M_MIDNIGHT,
                    LETTER_C_CLAMP,
                    LETTER_D_DUTY,
                    LETTER_I_ISOLATE
                };

            // Try to insert wrong clearances, expect -1 and errno == EINVAL
            std::array<char, 21> letters = {
                    'a', 'b', 'e', 'f', 'g', 'h',
                    'j', 'k', 'l', 'n', 'o', 'p',
                    'q', 'r', 't', 'u', 'v', 'w',
                    'x', 'y', 'z'
                };
            int letter_index = rand() % 21;
            char invalid_character = letters[letter_index];
            pid_t pid = getpid();

            if(print_enable) std::cout << "Im setting letter: " << invalid_character << " for the verify_third_function_error_handling_test" << std::endl;
            long returned = syscall(THIRD_FUNC_CHECK_SEC, pid, invalid_character);
            if(print_enable) std::cout << "SysCall GET_SEC returned: " << returned << std::endl;

            if((returned != -1) || (errno != EINVAL)) return false;
            if(print_enable) std::cout << "Just verified case of wrong values to GET_SEC, got expected result" << returned << std::endl;

            // Try to reach non-exsiting pid with a valid letter
            pid = pid_t(rand() % 3000);
            while(kill(pid, 0) == 0) {
                pid = pid_t(rand() % 3000);         // look for non-exsisting pid
            }
            returned = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_S_SWORD);
            if((returned != -1) || (errno != ESRCH)) return false;
            returned = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_M_MIDNIGHT);
            if((returned != -1) || (errno != ESRCH)) return false;
            returned = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_D_DUTY);
            if((returned != -1) || (errno != ESRCH)) return false;
            returned = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_C_CLAMP);
            if((returned != -1) || (errno != ESRCH)) return false;
            returned = syscall(THIRD_FUNC_CHECK_SEC, pid, LETTER_I_ISOLATE);
            if((returned != -1) || (errno != ESRCH)) return false;

            // Try to call a process without the correct clearance
            std::array<int, 5> array = generate_5_array();
            int flipper_bit = rand() % 5;
            array[flipper_bit] = 0;     // to be flipped
            if(print_enable) std::cout << "Im setting " << array << " for the verify_first_function_error_test" << std::endl;
            returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
            if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;

            std::array<int, 5> new_array = array;
            new_array[flipper_bit] = 1;        // flip the bit

            char flipped_letter = letters_decode[flipper_bit];

            int pipefd[2];
            if(pipe(pipefd) == -1) {return false;}

            pid = fork();                       // Fork to verify we inherit the clearance field

            if(pid == 0) {                      // Child process, should inherit the clearance field
                close(pipefd[0]); // pipe_shit

                if(print_enable) std::cout << "Im setting " << new_array << " to the child in verify_dynamic_fork_check_sec_test" << std::endl;
                returned = syscall(FIRST_FUNC_SET_SEC, new_array[0], new_array[1], new_array[2], new_array[3], new_array[4]);

                write(pipefd[1], "1", 1); // pipe_shit to annanuce the clearance field had been written
                close(pipefd[1]); // pipe_shit
                pause();                   // Wait for the kill
            }
            if(pid > 0) {                       // Parent process
                close(pipefd[1]); // pipe_shit

                char buffer; // pipe_shit
                read(pipefd[0], &buffer, 1); // Wait for child to finish the checkpoint
                close(pipefd[0]);

                // Get the clearance using the pid and third sys_call, one of them has to fail
                if(print_enable) std::cout << "Im setting " << flipped_letter << " letter to the child in verify_dynamic_fork_check_sec_test" << std::endl;
                returned = syscall(THIRD_FUNC_CHECK_SEC, pid, flipped_letter);
                if(print_enable) std::cout << "SysCall CHECK_SEC returned: " << returned << std::endl;
                if(print_enable) std::cout << "errno: " << errno << std::endl;
                if((returned != -1) || (errno != EPERM)) return false;

                kill(pid, SIGKILL);        // Kill child
                waitpid(pid, nullptr, 0);  // Reap zombie

                if(print_enable) std::cout << "I got " << returned << " for the verify_dynamic_fork_check_sec_test" << std::endl;
                if(print_enable) std::cout << "Just Verified " << pid << " 's clearance field" << std::endl;
            }
            if(pid < 0) {
                if(print_enable) std::cout << "Unexpected ERROR, verify_dynamic_fork_check_sec_test failed" << std::endl;
                return false;              // Fork failed
            }


            if(print_enable) std::cout << "verify_third_function_error_handling_test Passed for the " << i+1 << " time" << std::endl;
            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;
        }
        return true;
}

    bool verify_fourth_function_error_handling_test() {

    std::array<char, 5> letters_decode = {
        LETTER_S_SWORD,
        LETTER_M_MIDNIGHT,
        LETTER_C_CLAMP,
        LETTER_D_DUTY,
        LETTER_I_ISOLATE
    };

        if (seteuid(0) == -1) {                                                                                                                // Verify we run with root previllages
            std::cout << "Error test failed, Please run command with sudo: ./test" << std::endl;
            return 0;
        }

        for(int i=0 ; i<SHORT_TEST_ITERATIONS ; i++) {

            bool print_enable = false;

            if(print_enable) std::cout << "----------------------------------------------------------------------" << std::endl;

            // Try to insert wrong clearances, expect -1 and errno == EINVAL
            std::array<char, 21> letters = {
                    'a', 'b', 'e', 'f', 'g', 'h',
                    'j', 'k', 'l', 'n', 'o', 'p',
                    'q', 'r', 't', 'u', 'v', 'w',
                    'x', 'y', 'z'
                };
            int letter_index = rand() % 21;
            char invalid_character = letters[letter_index];
            if(print_enable) std::cout << "Im setting letter: " << invalid_character << " for the verify_fourth_function_error_handling_test" << std::endl;
            long returned = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, 1, invalid_character);
            if(print_enable) std::cout << "SysCall GET_SEC returned: " << returned << std::endl;

            if((returned != -1) || (errno != EINVAL)) return false;
            if(print_enable) std::cout << "Just verified case of wrong values to GET_SEC, got expected result" << returned << std::endl;
            if(print_enable) std::cout << "verify_fourth_function_error_handling_test Passed for the " << i+1 << " time" << std::endl;
            if(print_enable) std::cout << "-------------------------------------------------------------------" << std::endl;

            // Try to call a process without the correct clearance
            std::array<int, 5> array = generate_5_array();
            int flipper_bit = rand() % 5;
            array[flipper_bit] = 0;     // to be flipped
            if(print_enable) std::cout << "Im setting " << array << " for the verify_fourth_function_error_handling_test" << std::endl;
            returned = syscall(FIRST_FUNC_SET_SEC, array[0], array[1], array[2], array[3], array[4]);
            if(print_enable) std::cout << "SysCall SET_SEC returned: " << returned << std::endl;

            char flipped_letter = letters_decode[flipper_bit];
            if(print_enable) std::cout << "Im setting letter: " << flipped_letter << " for the verify_fourth_function_error_handling_test" << std::endl;

            returned = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, 1, flipped_letter);                         // ok height and wrong clearance
            if(print_enable) std::cout << "SysCall FLIP_SEC_BRANCH returned: " << returned << std::endl;
            if(print_enable) std::cout << "errno: " << errno << std::endl;
            if((returned != -1) || (errno != EPERM)) return false;

            returned = syscall(FOURTH_FUNC_FLIP_SEC_BRANCH, (letter_index * flipper_bit * (-19)), flipped_letter);     // wrong argument and no clearance
            if(print_enable) std::cout << "SysCall FLIP_SEC_BRANCH returned: " << returned << std::endl;
            if(print_enable) std::cout << "errno: " << errno << std::endl;
            if((returned != -1) || (errno != EINVAL)) return false;

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
            run_test("Simple check_sec test", verify_simple_check_sec_test);
            run_test("Init check_sec test", verify_init_check_sec_test);
            run_test("Non binary check_sec test", verify_non_binary_check_sec_test);
            run_test("Simple fork check_sec test", verify_simple_fork_check_sec_test);
            run_test("Dynamic fork check_sec test", verify_dynamic_fork_check_sec_test);            
            run_test("Init flip flip_sec_branch test", verify_simple_init_flip_sec_branch_test);   
            run_test("Big flip_sec_branch test", verify_flip_sec_branch_test);    
            
            run_test("First function error handling test", verify_first_function_error_handling_test);
            run_test("Second function error handling test", verify_second_function_error_handling_test);
            run_test("Third function error handling test", verify_third_function_error_handling_test);
            run_test("Fourth function error handling test", verify_fourth_function_error_handling_test);
           

            std::cout << "\nTest Summary:\n";
            if (failed_tests.empty()) {
                    std::cout << "All tests passed." << std::endl;
            }
            else {
                std::cout << failed_tests.size() << " test(s) failed: " << std::endl;
                for (const std::string& name : failed_tests) {
                        std::cout << " - " << name << std::endl;
                }
                std::cout << "Please modify print_enable = true in your failed tests" << std::endl;
            }

            system("pkill -9 -f ./test");

            return 0;

    }

    