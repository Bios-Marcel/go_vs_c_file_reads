package main

import (
	"fmt"
	"os"
)

func main() {
	dirName := "/home/marcel/scoop/buckets/main/bucket/"
	entries, err := os.ReadDir(dirName)
	if err != nil {
		fmt.Println("no dir")
		os.Exit(0)
	}

	for _, entry := range entries {
		fmt.Printf("%s\n", entry.Name())
		fileName := dirName + entry.Name()
		file, err := os.Open(fileName)
		if err != nil {
			os.Exit(1)
		}

		filesize, err := file.Seek(0, 2)
		if err != nil {
			os.Exit(1)
		}
		_, err = file.Seek(0, 0)
		if err != nil {
			os.Exit(1)
		}

		buffer := make([]byte, filesize)
		file.ReadAt(buffer, 0)
		fmt.Printf("%s", buffer)

		file.Close()
	}
}
