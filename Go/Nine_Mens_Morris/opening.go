package main

const WHITE = 1
const BLACK = 2

func leagalMoveOpening(x int, y int, fieldState [7][7]int) bool {
	result := false
	if fieldState[x][y] == 0 {
		result = true
	}
	return result
}
