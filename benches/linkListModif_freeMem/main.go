package main

import (
	"fmt"
	"runtime"
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
	var mem runtime.MemStats
	runtime.ReadMemStats(&mem)
	return mem.Alloc
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
