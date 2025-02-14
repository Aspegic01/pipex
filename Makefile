CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = pipex.c utils.c utils1.c
BSRC = pipex_bonus.c utils_bonus.c utils1_bonus.c
HEADERS = pipex.h
TARGET = pipex
BTARGET = pipex_bonus
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRC:.c=.o)
LIBFT_PATH = ./libft/

all: $(TARGET)

$(TARGET): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -L$(LIBFT_PATH) -lft

$(BTARGET): $(BOBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -o $(BTARGET) $(BOBJS) -L$(LIBFT_PATH) -lft

bonus: $(BTARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(TARGET) $(BTARGET)

re: fclean all

.PHONY: all bonus clean fclean re
