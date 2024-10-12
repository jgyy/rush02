#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

run_test() {
    local input="$1"
    local expected="$2"
    local description="$3"

    echo -n "Testing $description: "
    output=$(./rush-02 $input 2>&1)
    result=$(echo "$output" | grep -v "Debug:" | tr -d '\n')

    if [ "$result" == "$expected" ]; then
        echo -e "${GREEN}PASSED${NC}"
    else
        echo -e "${RED}FAILED${NC}"
        echo "  Input:    $input"
        echo "  Expected: $expected"
        echo "  Got:      $result"
        echo "  Full output:"
        echo "$output"
    fi
}

make

run_test "0" "zero" "zero"
run_test "1" "one" "one"
run_test "42" "forty two" "two-digit number"
run_test "100" "one hundred" "hundred"
run_test "1000" "one thousand" "thousand"
run_test "1000000" "one million" "million"
run_test "1000000000" "one billion" "billion"

run_test "1234567" "one million two hundred thirty four thousand five hundred sixty seven" "complex number"
run_test "999999999" "nine hundred ninety nine million nine hundred ninety nine thousand nine hundred ninety nine" "all nines"

run_test "10" "ten" "ten"
run_test "11" "eleven" "eleven"
run_test "20" "twenty" "twenty"
run_test "101" "one hundred one" "hundred and one"

run_test "-1" "Error" "negative number"
run_test "3.14" "Error" "decimal number"
run_test "12345678901234567890" "Error" "number too large"
run_test "abc" "Error" "non-numeric input"

echo "20 : twenty" > custom_dict.txt
echo "1 : one" >> custom_dict.txt
echo "0 : zero" >> custom_dict.txt
run_test "custom_dict.txt 21" "twenty one" "custom dictionary"

rm custom_dict.txt

echo "All tests completed."
