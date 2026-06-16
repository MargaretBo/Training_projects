package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	fmt.Println("Enter a grade: ")
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	score, _ := strconv.ParseInt(input, 10, 64)
	if score >= 60 {
		fmt.Println("Passed")
	} else {
		fmt.Println("Failed")
	}
}
