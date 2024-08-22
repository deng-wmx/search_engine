# 编译器和编译选项
CXX := g++
CXXFLAGS := -g
LDFLAGS := -lpthread -llog4cpp

# 源文件和目标文件
SRCS := $(wildcard *.cpp) ../../log4cpp/Mylogger.cpp
OBJS := $(SRCS:.cpp=.o)

# 最终生成的可执行文件
TARGET := server

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# 编译源文件生成目标文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

# 伪目标
.PHONY: all clean

