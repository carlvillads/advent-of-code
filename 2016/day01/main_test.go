package main

import "testing"

func TestSolvePart1(t *testing.T) {
	input := "R2, R3"

	got := solvePart1(input)
	want := 5

	if got != want {
		t.Fatalf("solvePart1() = %d, want %d", got, want)
	}

	input = "R2, R2, R2"
	got = solvePart1(input)
	want = 2
	if got != want {
		t.Fatalf("solvePart1() = %d, want %d", got, want)
	}

	input = "R5, L5, R5, R3"
	got = solvePart1(input)
	want = 12
	if got != want {
		t.Fatalf("solvePart1() = %d, want %d", got, want)
	}
}

func TestSolvePart2(t *testing.T) {
	input := "R8, R4, R4, R8"
	got := solvePart2(input)
	want := 4
	if got != want {
		t.Fatalf("solvePart2() = %d, want %d", got, want)
	}
}
