CC=g++ -std=c++17
EXEC=convertIt


all: $(EXEC)




clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(EXEC)
