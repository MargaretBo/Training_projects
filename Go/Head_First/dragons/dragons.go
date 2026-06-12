package main

func Hero(bullets, dragons int) bool {
	var result bool = false
	if bullets/2 >= dragons {
		result = true
	}
	return result
}
