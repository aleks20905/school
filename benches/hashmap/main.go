package main

import (
	"fmt"
	"time"
)

func main() {

	o := make(map[float64]float64)

	start := time.Now()
	for i := 0.0; i <= 10000000; i++ {
		o[i] = i + 10
	}

	fmt.Println("create time: ", time.Since(start))

	// time:  2.711069621s

	start = time.Now()
	for i := 0.0; i <= 10000000; i++ {
		o[i] = o[i] + i
	}

	fmt.Println("modify time: ", time.Since(start))
	// time:  1.638830667s

}
