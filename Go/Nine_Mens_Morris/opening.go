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

func moveWhite(x int, y int, fieldState [7][7]int) {
	if leagalMoveOpening(x, y, fieldState) {
		fieldState[x][y] = WHITE
	}
}

func moveBlack(x int, y int, fieldState [7][7]int) {
	if leagalMoveOpening(x, y, fieldState) {
		fieldState[x][y] = BLACK
	}
}

// func checkMills(color int, fieldState [7][7]int) {

// }

// func isInAMill(x int, y int, fieldState [7][7]int) bool {
// 	result := false
// 	if (x == 3) {
// 		if (y <= 2) {
// 			if (fieldState[])
// 		}
// 	}
// 	return result
// }
