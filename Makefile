CC = g++

BUILD_DIR = build
INCLUDE_DIR = include
SRC_DIR = src/


TARGET = $(BUILD_DIR)/ss

SRC  = $(SRC_DIR)paws/ss.cpp 
SRC += $(SRC_DIR)paws/reader.cpp $(SRC_DIR)main.cpp
SRC += $(SRC_DIR)paws/wikinet.cpp 
SRC += $(SRC_DIR)lapos/crf.cpp $(SRC_DIR)lapos/lookahead.cpp  $(SRC_DIR)lapos/crfpos.cpp $(SRC_DIR)lapos/tokenize.cpp $(SRC_DIR)lapos/lapos.cpp  

CFLAGS = -fPIC -Wall -W -O3 -pg -g -DNDEBUG
CFLAGS += -I$(INCLUDE_DIR)
CFLAGS += -I$(INCLUDE_DIR)/paws -I$(INCLUDE_DIR)/lapos


####################################################

TMP = $(SRC:.cpp=.o)
OBJ = $(TMP:.c=.o)

$(TARGET): $(OBJ) 
	@echo Linking $@ with flags: $(LDFLAGS)
	@$(CC) $(OBJ) -o $@ $(LDFLAGS) 
	@echo Build Complete


.cpp.o: $<
	@echo Compiling $<
	@$(CC) -c $(CFLAGS) $< -o $@

.c.o: $<
	@echo Compiling $<
	@gcc -c $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJ) $(TARGET)
	@echo All object files and binaries removed

dep: 
	@echo Running makedepend
	@makedepend -- $(CFLAGS) -- $(SRC) 2> /dev/null 
	@echo Completed makedepend


