package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func main() {
	fmt.Println("Enter a grade: ")
	reader := bufio.NewReader(os.Stdin)
	input, inputError := reader.ReadString('\n')
	if inputError != nil {
		log.Fatal(inputError)
	}
	input = strings.TrimSpace(input)
	score, error := strconv.ParseInt(input, 10, 64)
	if error != nil {
		log.Fatal(error)
	}
	if score >= 60 {
		fmt.Println("Passed")
	} else {
		fmt.Println("Failed")
	}
}
