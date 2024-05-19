package main

import (
	"fmt"
	"math"
	"os"
	"runtime"
	"strconv"
	"strings"
	"time"
)

type Coordinate struct {
	x float64
	y float64
	z float64
}

type Player struct {
	position Coordinate
}

func NewPlayer() *Player {
	return &Player{Coordinate{0, 0, 0}}
}
func (p *Player) MoveTo(cord []Coordinate) []Coordinate {
	if len(cord) < 2 {
		fmt.Println("Error: Not enough coordinates to determine direction")
		return nil
	}

	var directions []Coordinate
	prevCoord := cord[0]

	for i := range cord {
		currCoord := cord[i]
		dx := currCoord.x - prevCoord.x //нарочно да е малко по бавно
		dy := currCoord.y - prevCoord.y
		dz := currCoord.z - prevCoord.z
		direction := Coordinate{dx, dy, dz}
		directions = append(directions, direction)
		prevCoord = currCoord
	}
	return directions
}
func (p *Player) MoveToOffset(cord []Coordinate, offset float64) []Coordinate {
	if len(cord) < 2 {
		fmt.Println("Error: Not enough coordinates to determine direction")
		return nil
	}

	var directions []Coordinate
	prevCoord := cord[0]

	for i := range cord {
		currCoord := cord[i]
		dx := currCoord.x - prevCoord.x + offset
		dy := currCoord.y - prevCoord.y + offset
		dz := currCoord.z - prevCoord.z + offset
		direction := Coordinate{dx, dy, dz}
		directions = append(directions, direction)
		prevCoord = currCoord
	}
	return directions
}

func (p *Player) CalculateDistanceFromDirections(directions []Coordinate) float64 {
	if len(directions) < 1 {
		fmt.Println("Error: Not enough directions to determine distance traveled")
		return 0
	}

	totalDistance := 0.0
	for _, d := range directions {
		distance := math.Sqrt(d.x*d.x + d.y*d.y + d.z*d.z)
		totalDistance += distance
	}
	return totalDistance
}

func ReadAndParseFile() ([]Coordinate, error) {
	data, err := os.ReadFile("position.txt")
	if err != nil {
		return nil, fmt.Errorf("Error: Could not open file")
	}

	lines := strings.Split(string(data), "\n")
	var coordinates []Coordinate
	for _, line := range lines {
		if line == "" {
			continue
		}
		coords := strings.Fields(line)
		if len(coords) != 3 {
			return nil, fmt.Errorf("Error: Invalid data in file")
		}

		newX, err := strconv.ParseFloat(coords[0], 64)
		if err != nil {
			return nil, fmt.Errorf("Error: Invalid data in file")
		}
		newY, err := strconv.ParseFloat(coords[1], 64)
		if err != nil {
			return nil, fmt.Errorf("Error: Invalid data in file")
		}
		newZ, err := strconv.ParseFloat(coords[2], 64)
		if err != nil {
			return nil, fmt.Errorf("Error: Invalid data in file")
		}

		coordinates = append(coordinates, Coordinate{newX, newY, newZ})
	}

	return coordinates, nil
}

func printMemoryUsage() {
	var m runtime.MemStats
	runtime.ReadMemStats(&m)
	fmt.Printf("Memory Usage: %v KB\n", m.Alloc/1024)
}

func main() {

	coordinates, err := ReadAndParseFile()
	if err != nil {
		fmt.Println(err)
		return
	}

	start := time.Now()

	for i := range 100 {

		player := NewPlayer()
		directions := player.MoveTo(coordinates)
		_ = player.CalculateDistanceFromDirections(directions)
		//fmt.Printf("Distance Traveled: %f \n", distanceTraveled)

		directions = player.MoveToOffset(coordinates, float64(i))
		_ = player.CalculateDistanceFromDirections(directions)
		//fmt.Printf("Distance Traveled: %f \n", distanceTraveled)

		// directions := player.MoveTo(coordinates)
		// _ = player.CalculateDistanceFromDirections(directions)

		// directions = player.MoveToOffset(coordinates, float64(i))
		// _ = player.CalculateDistanceFromDirections(directions)
	}
	fmt.Printf("Time taken: %v ms \n", time.Since(start).Milliseconds())

	printMemoryUsage()

	// Time taken: 8014 ms
	// Memory Usage: 75972 KB
}
