all: main.o Food.o Restaurant.o Customer.o Order.o
	g++ -o a.out main.o Food.o Restaurant.o Customer.o Order.o
main.o: main.cpp Food.o Restaurant.o Customer.o Order.o
	g++ -c main.cpp
Food.o: Food.h Food.cpp
	g++ -c Food.cpp
Restaurant.o: Restaurant.h Restaurant.cpp Food.h
	g++ -c Restaurant.cpp
Customer.o: Customer.h Customer.cpp
	g++ -c Customer.cpp
Order.o: Order.h Order.cpp Customer.h Restaurant.h Food.h
	g++ -c Order.cpp
clean:
	rm -rf *.o
