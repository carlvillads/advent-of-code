package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type Direction int

const (
	North Direction = iota
	East
	South
	West
)

type Coordinate struct {
	X, Y int
}

type Person struct {
	Pos      Coordinate
	Pointing Direction
}

func (p *Person) followStep(turn string, blocks int) {
	if turn == "R" {
		p.Pointing = (p.Pointing + 1) % 4
	} else if turn == "L" {
		p.Pointing = (p.Pointing + 3) % 4 // Will wrap around
	}

	// fmt.Printf("I turned %s, now pointing %d\n", turn, p.Pointing)

	switch p.Pointing {
	case North:
		p.Pos.Y += blocks
	case East:
		p.Pos.X += blocks
	case South:
		p.Pos.Y -= blocks
	case West:
		p.Pos.X -= blocks
	}

	// fmt.Printf("I took %d steps. ", blocks)
	// fmt.Println("I am now at ", p.Pos)
}

func solvePart1(input string) int {
	input = strings.ReplaceAll(input, " ", "")
	me := Person{
		Pos:      Coordinate{0, 0},
		Pointing: 0, // North
	}

	for instruction := range strings.SplitSeq(input, ",") {
		turn := instruction[:1] // ???? I do not like this
		blocks, err := strconv.Atoi(strings.ReplaceAll(instruction[1:], "\n", ""))
		if err != nil {
			panic(err)
		}

		me.followStep(turn, blocks)
	}

	x := int(math.Abs(float64(me.Pos.X)))
	y := int(math.Abs(float64(me.Pos.Y)))
	return x + y
}

func solvePart2(input string) int {
	input = strings.ReplaceAll(input, " ", "")
	me := Person{
		Pos:      Coordinate{0, 0},
		Pointing: North,
	}
	visited := map[Coordinate]struct{}{
		{X: 0, Y: 0}: {},
	}

	for instruction := range strings.SplitSeq(input, ",") {
		turn := instruction[:1]
		blocks, err := strconv.Atoi(strings.ReplaceAll(instruction[1:], "\n", ""))
		if err != nil {
			panic(err)
		}

		if turn == "R" {
			me.Pointing = (me.Pointing + 1) % 4
		} else if turn == "L" {
			me.Pointing = (me.Pointing + 3) % 4
		}

		switch me.Pointing {
		case North:
			for range blocks {
				me.Pos.Y++

				if _, ok := visited[me.Pos]; ok {
					return int(math.Abs(float64(me.Pos.X))) + int(math.Abs(float64(me.Pos.Y)))
				}

				visited[me.Pos] = struct{}{}
			}
		case East:
			for range blocks {
				me.Pos.X++

				if _, ok := visited[me.Pos]; ok {
					return int(math.Abs(float64(me.Pos.X))) + int(math.Abs(float64(me.Pos.Y)))
				}

				visited[me.Pos] = struct{}{}
			}
		case South:
			for range blocks {
				me.Pos.Y--

				if _, ok := visited[me.Pos]; ok {
					return int(math.Abs(float64(me.Pos.X))) + int(math.Abs(float64(me.Pos.Y)))
				}

				visited[me.Pos] = struct{}{}
			}
		case West:
			for range blocks {
				me.Pos.X--

				if _, ok := visited[me.Pos]; ok {
					return int(math.Abs(float64(me.Pos.X))) + int(math.Abs(float64(me.Pos.Y)))
				}

				visited[me.Pos] = struct{}{}
			}
		}
	}

	return 0
}

func main() {
	data, err := os.ReadFile("inputs/day01.txt")
	if err != nil {
		panic(err)
	}

	part1 := solvePart1(string(data))
	part2 := solvePart2(string(data))

	fmt.Printf("Part 1: Easter Bunny HQ is %d blocks away.\n", part1)
	fmt.Printf("Part 2: The actual location of Easter Bunny HQ is %d blocks away.\n", part2)
}
