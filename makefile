CC=g++ --std=c++17
EXEC=convertIt


all: main.cpp Auteur.o Titre.o
	$(CC) Auteur.o Titre.o main.cpp -o $(EXEC)

%.o: %.cpp
	$(CC) -c $< 
	

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
