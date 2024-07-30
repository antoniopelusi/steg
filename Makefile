NAME = steg
SRC_PATH = src/
TEST_PATH = test/
BIN_PATH = bin/
INSTALL_PATH = /usr/local/bin/
FLAGS = -lpng -lz

TEST_PWD = 1234
TEST_INPUT_TXT = input.txt
TEST_INPUT_IMAGE = input.png
TEST_OUTPUT_IMAGE = output.png

RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m

.SILENT: clear compile test install uninstall

all: compile

setup:
	echo "$(CYAN)|>$(RESET) installing dependencies\n"
	sudo apt install libpng-dev -y

clear:
	echo "$(RED)|>$(RESET) clear\n"
	rm -rf bin/
	rm -f output.png
	rm -f output.txt

compile: clear
	echo "$(YELLOW)|>$(RESET) compile\n"
	mkdir $(BIN_PATH)
	gcc $(SRC_PATH)/*.c -o $(BIN_PATH)$(NAME) $(FLAGS)

test: install
	echo "$(GREEN)|>$(RESET) run test\n"
	$(NAME) -w $(TEST_PATH)$(TEST_INPUT_IMAGE) $(TEST_PWD) $(TEST_PATH)$(TEST_INPUT_TXT)
	$(NAME) -r $(TEST_OUTPUT_IMAGE) $(TEST_PWD)

install: compile
	echo "$(CYAN)|>$(RESET) install\n"
	sudo cp $(BIN_PATH)$(NAME) $(INSTALL_PATH)

uninstall:
	echo "$(CYAN)|>$(RESET) uninstall\n"
	sudo rm -f $(INSTALL_PATH)$(NAME)