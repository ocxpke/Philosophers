#!/bin/bash

# Philosophers Test Suite
# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Contadores
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}   PHILOSOPHERS TEST SUITE      ${NC}"
echo -e "${BLUE}================================${NC}"

# Función para ejecutar una prueba
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_behavior="$3"
    local timeout_duration="$4"
    
    echo -e "\n${YELLOW}Testing: $test_name${NC}"
    echo -e "Command: ${BLUE}$command${NC}"
    echo -e "Expected: $expected_behavior"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Ejecutar con timeout
    timeout $timeout_duration $command > test_output.tmp 2>&1
    local exit_code=$?
    
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}❌ TIMEOUT: Test exceeded $timeout_duration${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    elif [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✅ PASSED: Program executed successfully${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}❌ FAILED: Program crashed or returned error${NC}"
        echo -e "${RED}Exit code: $exit_code${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    
    # Mostrar parte del output para análisis
    if [ -f test_output.tmp ]; then
        echo -e "${BLUE}Output sample:${NC}"
        head -10 test_output.tmp
        if [ $(wc -l < test_output.tmp) -gt 10 ]; then
            echo "... (truncated)"
        fi
    fi
    
    rm -f test_output.tmp
}

# Función para pruebas de argumentos inválidos
test_invalid_args() {
    echo -e "\n${BLUE}=== TESTING INVALID ARGUMENTS ===${NC}"
    
    run_test "No arguments" "./philo" "Should print error message" "2s"
    run_test "Too few arguments" "./philo 5 800" "Should print error message" "2s"
    run_test "Too many arguments" "./philo 5 800 200 200 7 extra" "Should print error message" "2s"
    run_test "Zero philosophers" "./philo 0 800 200 200" "Should exit with error" "2s"
    run_test "Negative time_to_die" "./philo 5 -800 200 200" "Should exit with error" "2s"
    run_test "Zero time_to_eat" "./philo 5 800 0 200" "Should exit with error" "2s"
    run_test "Negative time_to_sleep" "./philo 5 800 200 -200" "Should exit with error" "2s"
    run_test "Invalid eat count" "./philo 5 800 200 200 0" "Should exit with error" "2s"
}

# Función para pruebas básicas de funcionalidad
test_basic_functionality() {
    echo -e "\n${BLUE}=== TESTING BASIC FUNCTIONALITY ===${NC}"
    
    run_test "Single philosopher (should die)" "./philo 1 800 200 200" "Philosopher should die" "5s"
    run_test "Two philosophers" "./philo 2 800 200 200" "Should run without dying" "10s"
    run_test "Five philosophers" "./philo 5 800 200 200" "Should run without dying" "15s"
    run_test "Large number of philosophers" "./philo 200 800 200 200" "Should handle many threads" "10s"
}

# Función para pruebas de supervivencia
test_survival() {
    echo -e "\n${BLUE}=== TESTING SURVIVAL SCENARIOS ===${NC}"
    
    run_test "Easy survival" "./philo 4 410 200 200" "No one should die" "15s"
    run_test "Tight timing" "./philo 5 800 200 200" "Should survive" "20s"
    run_test "Very tight timing" "./philo 4 310 200 100" "Should survive" "15s"
}

# Función para pruebas de muerte
test_death_scenarios() {
    echo -e "\n${BLUE}=== TESTING DEATH SCENARIOS ===${NC}"
    
    run_test "Quick death" "./philo 4 200 400 100" "Someone should die quickly" "3s"
    run_test "Single philo death" "./philo 1 400 200 200" "Should die (can't eat with one fork)" "3s"
    run_test "Starvation test" "./philo 5 300 200 150" "Should detect death quickly" "5s"
}

# Función para pruebas con número fijo de comidas
test_meal_count() {
    echo -e "\n${BLUE}=== TESTING MEAL COUNT SCENARIOS ===${NC}"
    
    run_test "Everyone eats once" "./philo 5 800 200 200 1" "Should stop after everyone eats once" "10s"
    run_test "Everyone eats 3 times" "./philo 4 800 200 200 3" "Should stop after everyone eats 3 times" "15s"
    run_test "High meal count" "./philo 3 800 200 200 10" "Should stop after 10 meals each" "30s"
}

# Función para pruebas de estrés
test_stress() {
    echo -e "\n${BLUE}=== STRESS TESTING ===${NC}"
    
    run_test "Many philosophers" "./philo 100 800 200 200" "Should handle 100 philosophers" "15s"
    run_test "Very fast eating" "./philo 5 800 50 50" "Should handle fast cycles" "10s"
    run_test "Long simulation" "./philo 4 800 200 200 20" "Should run for many cycles" "60s"
}

# Función para verificar formato de output
check_output_format() {
    echo -e "\n${BLUE}=== CHECKING OUTPUT FORMAT ===${NC}"
    
    echo "Running format check..."
    timeout 5s ./philo 4 800 200 200 2 > format_check.tmp 2>&1
    
    if [ -f format_check.tmp ]; then
        echo -e "${BLUE}Checking timestamp format...${NC}"
        if grep -E "^\[[0-9]+\] [0-9]+ (has taken a fork|is eating|is sleeping|is thinking|died)$" format_check.tmp > /dev/null; then
            echo -e "${GREEN}✅ Output format looks correct${NC}"
        else
            echo -e "${RED}❌ Output format may be incorrect${NC}"
            echo -e "${YELLOW}Expected format: [timestamp] philosopher_id action${NC}"
        fi
        
        echo -e "${BLUE}Sample output:${NC}"
        head -10 format_check.tmp
        
        rm -f format_check.tmp
    fi
}

# Función para verificar data races con helgrind
check_data_races() {
    echo -e "\n${BLUE}=== CHECKING FOR DATA RACES ===${NC}"
    
    if command -v valgrind >/dev/null 2>&1; then
        echo "Running Helgrind to detect data races..."
        echo -e "${YELLOW}This may take a while...${NC}"
        
        timeout 30s valgrind --tool=helgrind --log-file=helgrind.log ./philo 4 800 200 200 2 > /dev/null 2>&1
        
        if [ -f helgrind.log ]; then
            if grep -q "ERROR SUMMARY: 0 errors" helgrind.log; then
                echo -e "${GREEN}✅ No data races detected!${NC}"
            else
                echo -e "${RED}❌ Potential data races detected${NC}"
                echo -e "${YELLOW}Check helgrind.log for details${NC}"
                grep -A 5 -B 5 "Race condition" helgrind.log | head -20
            fi
            rm -f helgrind.log
        fi
    else
        echo -e "${YELLOW}⚠️  Valgrind not available, skipping data race check${NC}"
    fi
}

# Función para verificar memory leaks
check_memory_leaks() {
    echo -e "\n${BLUE}=== CHECKING FOR MEMORY LEAKS ===${NC}"
    
    if command -v valgrind >/dev/null 2>&1; then
        echo "Running Valgrind to detect memory leaks..."
        
        timeout 15s valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind.log ./philo 4 800 200 200 2 > /dev/null 2>&1
        
        if [ -f valgrind.log ]; then
            if grep -q "All heap blocks were freed" valgrind.log; then
                echo -e "${GREEN}✅ No memory leaks detected!${NC}"
            else
                echo -e "${RED}❌ Memory leaks detected${NC}"
                echo -e "${YELLOW}Check valgrind.log for details${NC}"
                grep -A 10 "LEAK SUMMARY" valgrind.log
            fi
            rm -f valgrind.log
        fi
    else
        echo -e "${YELLOW}⚠️  Valgrind not available, skipping memory leak check${NC}"
    fi
}

# Compilar el programa
echo -e "${BLUE}Compiling program...${NC}"
make re
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Compilation failed!${NC}"
    exit 1
fi
echo -e "${GREEN}✅ Compilation successful${NC}"

# Ejecutar todas las pruebas
test_invalid_args
test_basic_functionality
test_survival
test_death_scenarios
test_meal_count
test_stress
check_output_format
check_data_races
check_memory_leaks

# Resumen final
echo -e "\n${BLUE}================================${NC}"
echo -e "${BLUE}         TEST SUMMARY           ${NC}"
echo -e "${BLUE}================================${NC}"
echo -e "Total tests: $TOTAL_TESTS"
echo -e "${GREEN}Passed: $PASSED_TESTS${NC}"
echo -e "${RED}Failed: $FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    echo -e "${GREEN}Your implementation looks good!${NC}"
else
    echo -e "\n${RED}❌ Some tests failed${NC}"
    echo -e "${YELLOW}Review the failed tests and fix the issues${NC}"
fi

# Limpiar archivos temporales
rm -f test_output.tmp format_check.tmp valgrind.log helgrind.log

echo -e "\n${BLUE}Test suite completed!${NC}"