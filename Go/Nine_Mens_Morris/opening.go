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

func isInAMill(x int, y int, fieldState [7][7]int) bool {
	result := false
	color := fieldState[x][y]
	if x == 3 {
		if y <= 2 {
			if fieldState[3][0] == color && fieldState[3][1] == color && fieldState[3][2] == color {
				result = true
			}
		} else {
			if fieldState[3][4] == color && fieldState[3][5] == color && fieldState[3][6] == color {
				result = true
			}
		}

	}
	if y == 3 {
		if x <= 2 {
			if fieldState[0][3] == color && fieldState[1][3] == color && fieldState[2][3] == color {
				result = true
			}
		} else {
			if fieldState[4][3] == color && fieldState[5][3] == color && fieldState[6][3] == color {
				result = true
			}
		}
	}
	if x != 3 && y != 3 {
		colorCountX := 0
		colorCountY := 0
		for i := 0; i < 7; i++ {
			if fieldState[x][i] == color {
				colorCountX++
			}
			if fieldState[i][y] == color {
				colorCountY++
			}
		}
		if colorCountX == 3 || colorCountY == 3 {
			result = true
		}
	}
	return result
}
