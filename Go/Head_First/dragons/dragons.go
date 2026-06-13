package main

import "fmt"

func Hero(bullets, dragons int) bool {
	var result bool = false
	if bullets/2 >= dragons {
		result = true
	}
	return result
}

func main() {
	fmt.Println(Hero(2, 2))
	fmt.Println(Hero(4, 2))
	fmt.Println(Hero(7, 3))
}
