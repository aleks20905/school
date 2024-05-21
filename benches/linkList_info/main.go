package main

import (
	"fmt"
	"io/ioutil"
	"syscall"
	"time"
	"unsafe"
)

type Node struct {
	next *Node
	val  float64
}

var nodes *Node = nil

func iterateAndPlace(val float64) {
	node := nodes
	var prev *Node = nil

	for node != nil {
		if node.val > 99999 {
			break
		}
		prev = node
		node = node.next
	}

	prev.val = val
}

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
	x := Node{}
	fmt.Printf("Size of struct: %d\n", unsafe.Sizeof(x)) // 16 bytes

	initialValue := 0.0
	for i := 0; i < 3000; i++ {
		newNode := new(Node)
		newNode.next = nodes
		newNode.val = initialValue
		nodes = newNode
		initialValue += 1
	}

	for retrys := 50; retrys < 1000000; retrys += int(float32(retrys) * 0.15) {
		start := time.Now()
		for i := 0; i < retrys; i++ {
			iterateAndPlace(100.1)
		}
		end := time.Now()

		diff := end.Sub(start)

		wallClockTime := diff.Milliseconds()
		memoryUsage := getMemoryUsage()

		fmt.Printf("Time: %7d ms Memory Usage: %9d bytes \n", wallClockTime, memoryUsage)
	}
}
