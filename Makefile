CC = gcc

CFLAGS += -Wall -O2 -Iinclude
LDFLAGS += -lssh

NAME = ssh-runner
SRCS := main.c \
	config.c \
	ssh_run.c
OBJS := $(SRCS:%.c=obj/%.o)

all: dirs $(NAME) 

dirs:
	@mkdir -p obj

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $@
	@echo Linking

$(OBJS): obj/%.o : src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo Compiling

clean:
	rm -f $(OBJS)
	rm -f $(NAME)
