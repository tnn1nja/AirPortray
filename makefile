app_name = main

main_src = src/main.cpp
main_obj = build/main.o
test_src = src/test.o
test_obj = build/test.o

$(app_name): $(main_obj) $(test_obj)
	g++ $(main_obj) $(test_obj) -o $(app_name)

$(main_obj): $(main_src)
	g++ -c $(main_src) -o $(main_obj)

$(test_obj): $(test_src)
	g++ -c $(test_src) -o $(test_obj)