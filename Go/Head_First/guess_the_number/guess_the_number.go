package main

import (
	"bufio"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"strings"
)

func main() {
	guessed := false
	target := rand.Intn(100) + 1
	for range 10 {
		fmt.Println("Enter a guess: ")
		reader := bufio.NewReader(os.Stdin)
		input, inputError := reader.ReadString('\n')
		if inputError != nil {
			log.Fatal(inputError)
		}
		input = strings.TrimSpace(input)
		guess, error := strconv.ParseInt(input, 10, 64)
		if error != nil {
			log.Fatal(error)
		}
		if guess > int64(target) {
			fmt.Println("Oops, your guess is too High")
		} else if guess < int64(target) {
			fmt.Println("Oops, your guess is too Low")
		} else {
			fmt.Println("Good job! You guessed right")
			guessed = true
			break
		}
	}
	if !guessed {
		fmt.Println("Sorry. You didn't guess my number. It was:" + strconv.Itoa(target))
	}
}
