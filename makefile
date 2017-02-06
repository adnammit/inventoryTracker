
# COMPILER:
CC=g++

# FLAGS:
CFLAGS=-g -c
LDFLAGS=

#EXECUTABLE:
EXE=play

# SOURCE FILES:
SOURCES=main.cpp product.cpp node.cpp

# OBJECT FILES:
OBJECTS=$(SOURCES:.cpp=.o)



all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
    
clean:	
	rm -rf *.o play
