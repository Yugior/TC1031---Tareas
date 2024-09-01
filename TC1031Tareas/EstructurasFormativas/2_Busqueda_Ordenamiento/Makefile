# Makefile para un proyecto que utiliza archivos .cpp y .h

# Nombre del ejecutable
TARGET = programa

# Archivos fuente
SRCS = main.cpp Sorts.cpp

# Archivos objeto
OBJS = $(SRCS:.cpp=.o)

# Compilador
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Regla por defecto
all: $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Regla para construir los archivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET) $(OBJS)
