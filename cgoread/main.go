package main

import (
	"fmt"
	"os"
	"unsafe"
)

/*
#include <string.h>
#include "main.c"
*/
import "C"

func main() {
	dirName := "/home/marcel/scoop/buckets/main/bucket/"
	entries, err := os.ReadDir(dirName)
	if err != nil {
		fmt.Println("no dir")
		os.Exit(0)
	}

	for _, entry := range entries {
		if entry == nil {
			continue	
		}

		fileName := dirName + entry.Name()
		var bufferPointer *C.char
		size := C.fileToBuffer(C.CString(fileName), &bufferPointer)
		if bufferPointer == nil {
			continue
		}
		buffer := unsafe.Slice((*byte)(unsafe.Pointer(bufferPointer)), int(size))
		fmt.Print(string(buffer))
		C.free(unsafe.Pointer(bufferPointer))
	}
}
