CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

all: prepare gds2ascii

prepare:
	@ mkdir -p obj

gds2ascii: $(OBJ_FILES)
	@ g++ -o $@ $^

obj/%.o: src/%.cpp
	@ g++ -c -o $@ $<

clean:
	@ rm -rf obj
	@ rm -f gds2ascii

