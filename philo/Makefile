NAME	:= philo
CFLAGS	:= -Wextra -Wall -Werror -lpthread

SRCS	:= src/main.c src/visuals.c src/utils.c src/init.c src/monitoring.c src/parsing.c src/behaviour.c src/Controller.c
OBJS	:= ${SRCS:.c=.o}
all: $(NAME)

define PRINT_LOADING
	@printf "["
	@for i in $(shell seq 0 10 100); do \
		printf "▓"; \
		sleep 0.01; \
	done
	@printf "] 100%%$(RESET)\n"
endef

%.o: %.c
	@echo "\033[32;1m ->$(notdir $<)\033[0m"
	@$(PRINT_LOADING)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@echo "\033[32;1mcleaned\033[0m"
	@rm -rf $(BOBJS)
	@rm -rf $(OBJS)

fclean: clean
	@echo "\033[32;1mfcleaned\033[0m"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re