# 变量定义
CXX := g++
CXXFLAGS := -g
LDFLAGS := -lpthread -llog4cpp
SRC := $(wildcard *.cpp) ../log4cpp/Mylogger.cpp
OBJ := $(SRC:.cpp=.o)
TARGET := my_program

# 规则定义
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

# 编译每个源文件成目标文件的规则
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

../log4cpp/%.o: ../log4cpp/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

