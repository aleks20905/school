package main

import (
	"fmt"
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

func main() {
	x := Node{}
	fmt.Printf("Size of struct: %d\n", unsafe.Sizeof(x)) // 16 bytes

	for i := 0; i < 3000; i++ {
		newNode := new(Node)
		newNode.next = nodes
		nodes = newNode
	}

	start := time.Now()
	for i := 0; i < 1000000; i++ {
		iterateAndPlace(100.1)
		iterateAndAdd(float64(i) + 15.56)
	}
	fmt.Printf("%v\n", time.Since(start).Milliseconds())
}
