.PHONY = default clear build run

default: build run

clear:
	rm -rf server client
build:
	g++ server.cpp -o server
	g++ client.cpp -o client
run:
	./server & ./client
