CC=g++ --std=c++11
EXEC=convertIt


all: Source.cpp Auteur.o Titre.o
	$(CC) Auteur.o Titre.o Source.cpp -o $(EXEC)

%.o: %.cpp
	$(CC) -c $< 
	

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
