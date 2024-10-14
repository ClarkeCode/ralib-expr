
all:
	g++ -o target.exe raymain.cpp -lraylib -lgdi32 -lwinmm
	./target.exe && rm target.exe
