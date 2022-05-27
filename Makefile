NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
LIBFT		= libft/libft.a
INCLUDE		= includes/
READLINE	= -L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
SRC_DIR		= srcs
OBJ_DIR		= objs
SRCS		= $(wildcard $(SRC_DIR)/*.c)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@make -s -C libft
	@echo "[+] libft compiled"
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(LIBFT) -o $@ $(READLINE)
	@echo "[+] $(NAME) compiled"

all: $(NAME)

clean:
	@make -s -C libft clean
	@echo "[+] libft cleaned"
	@$(RM) $(OBJ_DIR)
	@echo "[+] $(NAME) cleaned"

fclean: clean
	@make -s -C libft fclean
	@echo "[+] libft fcleaned"
	@$(RM) $(NAME)
	@echo "[+] $(NAME) fcleaned"

re: fclean all

test: all
	@./$(NAME)

run: test

var: all
	@valgrind --leak-check=full ./$(NAME)
val: var

leaks: all
	@leaks --atExit -- ./$(NAME)

up:
	@$(RM) ../$(NAME)_backup
	@mkdir -p ../$(NAME)_backup
	@cp -r * ../$(NAME)_backup
	@echo "[+] Backuped"
backup: up

push:
	git add .
	git commit -m "makefile auto commit"
	git push
tar:
	@tar -cf ../$(NAME).tar .
	@echo "[+] Tarred"

.PHONY: all clean fclean re $(NAME)
