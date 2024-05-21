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

func iterateAndAdd(i float64) {
	node := nodes
	for node != nil {
		node.val += i
		node = node.next
	}
}

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

	if prev != nil {
		prev.val = val
	}
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
func calNode(n int) {

	for i := 0; i < n; i++ {
		newNode := new(Node)
		newNode.next = nodes
		nodes = newNode
	}

	start := time.Now()
	for i := 0; i < 10000; i++ {
		iterateAndPlace(100.1)
		iterateAndAdd(float64(i) + 15.56)
	}
	fmt.Printf("node N:%v  %v ms mem usage: %v\n", n, time.Since(start).Milliseconds(), getMemoryUsage())
	nodes = nil
}

func main() {
	x := Node{}
	fmt.Printf("Size of struct: %d\n", unsafe.Sizeof(x)) // 16 bytes
	for i := 200; i < 10000; i += 200 {
		calNode(i)
	}

}
