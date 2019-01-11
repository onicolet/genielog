CC=g++ --std=c++11
EXEC=convertIt


all: Source.cpp Auteur.o Titre.o Structure.o
	$(CC) Auteur.o Structure.o Titre.o Source.cpp -o $(EXEC)

%.o: %.cpp
	$(CC) -c $< 
	

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
