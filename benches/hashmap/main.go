package main

import (
	"fmt"
	"time"
)

func main() {

	o := make(map[float64]float64)

	var i float64 = 0

	start := time.Now()
	for ; i <= 10000000; i++ {
		o[i] = i + 10
	}

	fmt.Println("time: ", time.Since(start))

	// time:  3.191081661s

}
