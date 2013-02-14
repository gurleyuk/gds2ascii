CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

gds2ascii: $(OBJ_FILES)
	g++ -o $@ $^

obj/%.o: src/%.cpp
	g++ -c -o $@ $<

clean:
	rm -f obj/*.o
	rm -f gds2ascii
