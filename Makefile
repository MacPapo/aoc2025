CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Werror -Wno-unused-parameter -fsanitize=address,undefined
LDFLAGS = -fsanitize=address,undefined

DAYS_DIR = days
BUILD_DIR = build
SRC_DIR = .
UTILS = $(SRC_DIR)/utils.c

DAYS = $(sort $(patsubst $(DAYS_DIR)/day%/main.c,%,$(wildcard $(DAYS_DIR)/day*/main.c)))

all: $(DAYS)

$(DAYS): %: $(BUILD_DIR)/day%

$(BUILD_DIR)/day%: $(DAYS_DIR)/day%/main.c $(UTILS) | $(BUILD_DIR)
	@echo "Compilando day$*..."
	$(CC) $(CFLAGS) -I. -o $@ $< $(UTILS) $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run%: $(BUILD_DIR)/day%
	@echo "=== Day $* ==="
	@./$(BUILD_DIR)/day$* $(DAYS_DIR)/day$*/input.txt

clean:
	rm -rf $(BUILD_DIR)

compile_commands.json: clean
	bear -- make -B

newday:
	@if [ -z "$(DAY)" ]; then \
		echo "Errore: specifica il giorno con make newday DAY=1"; exit 1; \
	fi; \
	DAY_PAD="$$(printf "%02d" $$(echo $(DAY) | sed 's/^0*//'))"; \
	DIR="days/day$$DAY_PAD"; \
	mkdir -p "$$DIR"; \
	if [ ! -f "$$DIR/main.c" ]; then \
		sed "s/DAY/$$DAY_PAD/g" template.c > "$$DIR/main.c"; \
		echo "Creato $$DIR/main.c"; \
	else \
		echo "$$DIR/main.c esiste già"; \
	fi; \
	touch "$$DIR/input.txt"; \
	echo "Giorno $$DAY_PAD pronto! Usa: make && make run$$DAY_PAD"

.PHONY: all clean run% newday $(DAYS)
