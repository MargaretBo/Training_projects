package main

import "fmt"

func main() {
	var price int = 100
	fmt.Println("Price is", price, "dollars")
	var taxRate float64 = 0.08
	var tax float64 = float64(price) * taxRate
	fmt.Println("Tax is", tax, "dollars")
	var total float64 = float64(price) + tax
	fmt.Println("Total cost is", total, "dollars")
	var avaliableFunds int = 120
	fmt.Println(avaliableFunds, "avaliable")
	fmt.Println("Within budget?", float64(avaliableFunds) >= total)
}
