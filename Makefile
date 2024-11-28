# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/usr/local/include

# Каталоги и файлы
SRCDIR = .
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = server

# Флаги и библиотеки
LDFLAGS = -L/usr/local/lib -lcryptopp

# Правила
all: $(TARGET) clean

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

.PHONY: all clean
