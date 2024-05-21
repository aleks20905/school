package main

import (
	"fmt"
	"io/ioutil"
	"syscall"
	"time"
)

func getMemoryUsage() uint64 {
	data, err := ioutil.ReadFile("/proc/self/statm")
	if err != nil {
		fmt.Println("Error: Could not open /proc/self/statm")
		return 0
	}

	fields := string(data)
	var size, resident, share, text, lib, dataValue, dt uint64
	fmt.Sscanf(fields, "%d %d %d %d %d %d %d", &size, &resident, &share, &text, &lib, &dataValue, &dt)

	pageSize := uint64(syscall.Getpagesize()) // In bytes
	residentSize := resident * pageSize

	return residentSize
}

func main() {

	o := make(map[float64]float64)
	fmt.Println("mem: ", getMemoryUsage())
	// mem:  1835008

	start := time.Now()
	for i := 0.0; i <= 10000000; i++ {
		o[i] = i + 10
	}

	fmt.Println("create time: ", time.Since(start))
	fmt.Println("mem: ", getMemoryUsage())

	// time:  2.711069621s
	// mem:  644612096

	start = time.Now()
	for i := 0.0; i <= 10000000; i++ {
		o[i] = o[i] + i
	}

	fmt.Println("modify time: ", time.Since(start))
	fmt.Println("mem: ", getMemoryUsage())

	// time:  1.638830667s
	// mem:  644612096

}
