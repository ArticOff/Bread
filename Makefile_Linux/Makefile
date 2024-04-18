GPLUS=g++

SRC=../src/main.cpp ../src/tokenizer.cpp ../src/parser/parser.cpp ../src/parser/instruction_maker_functions.cpp ../src/execute/execute.cpp ../src/execute/instruction_reader_functions.cpp ../src/methods.cpp
OBJ=$(SRC:.c=.o)
EXEC=../bin/Bread

all: $(EXEC)

$(EXEC): $(OBJ)
	$(GPLUS) -o $@ $^

%.o: %.c
	$(GPLUS) -o $@ $<

clear:
	rm -f $(OBJ) $(EXEC)