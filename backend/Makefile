CXX = g++
CXXFLAGS = -Wall -std=c++20 

INCDIR = -Iinclude/
LIBDIR =

SRC = src/grammar.cpp \
      src/ll1_parser.cpp \
      src/symbol_table.cpp

OBJ = $(SRC:.cpp=.o)

TEST_SRC = tests/tests.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_TARGET = run_tests
GTEST_LIBS = -lgtest -lgtest_main -lpthread
all: $(TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(filter-out main.o, $(OBJ))
	$(CXX) $(OBJ) $(TEST_OBJ) -o $(TEST_TARGET) $(LIBDIR) $(GTEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIR) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(OBJ) $(TARGET)

format:
	@find . -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i

re: fclean all

-include $(SRC:.cpp=.d)

