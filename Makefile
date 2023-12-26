# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/10 19:56:15 by sbouabid          #+#    #+#              #
#    Updated: 2023/12/11 17:30:28 by sbouabid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f

CLIENT_SRC		= client.c
CLIENT_OBJ		= $(CLIENT_SRC:.c=.o)

SERVER_SRC		= server.c
SERVER_OBJ		= $(SERVER_SRC:.c=.o)

HELPER_SRC		= utils.c
HELPER_OBJ      = $(HELPER_SRC:.c=.o)

CLIENT_EX       = client
SERVER_EX       = server

CLIENT_SRC_BONUS        = client_bonus.c
CLIENT_OBJ_BONUS        = $(CLIENT_SRC_BONUS:.c=.o)
CLIENT_EX_BONUS         = client_bonus

SERVER_SRC_BONUS        = server_bonus.c
SERVER_OBJ_BONUS        = $(SERVER_SRC_BONUS:.c=.o)
SERVER_EX_BONUS         = server_bonus

HELPER_SRC_BONUS        = utils_bonus.c
HELPER_OBJ_BONUS        = $(HELPER_SRC_BONUS:.c=.o)


all: $(CLIENT_EX) $(SERVER_EX)
	@echo "✔️ ALL GOOD"

%.o: %.c minitalk.h
	@$(CC) $(CFLAGS) -c $<
%_bonus.h: %_bonus.c minitalk_bonus.h
	@$(CC) $(CFLAGS) -c $<

$(CLIENT_EX): $(CLIENT_OBJ) $(HELPER_OBJ)
	@$(CC) $(CFLAGS) $(CLIENT_OBJ) $(HELPER_OBJ) -o $(CLIENT_EX)
	
$(SERVER_EX): $(SERVER_OBJ)
	@$(CC) $(CFLAGS) $(SERVER_OBJ) $(HELPER_OBJ) -o $(SERVER_EX)


bonus: $(CLIENT_EX_BONUS) $(SERVER_EX_BONUS)
	@echo "✔️ ALL GOOD: BONUS"
$(CLIENT_EX_BONUS): $(CLIENT_OBJ_BONUS) $(HELPER_OBJ_BONUS)
	@$(CC) $(CFLAGS) $(CLIENT_OBJ_BONUS) $(HELPER_OBJ_BONUS) -o $(CLIENT_EX_BONUS)

$(SERVER_EX_BONUS): $(SERVER_OBJ_BONUS) $(HELPER_OBJ_BONUS)
	@$(CC) $(CFLAGS) $(SERVER_OBJ_BONUS) $(HELPER_OBJ_BONUS) -o $(SERVER_EX_BONUS)

clean:
	@$(RM) $(CLIENT_OBJ) $(CLIENT_OBJ_BONUS) $(SERVER_OBJ) $(SERVER_OBJ_BONUS) $(HELPER_OBJ) $(HELPER_OBJ_BONUS)
	@echo "CLEAN ✔️"
fclean: clean
	@$(RM) $(CLIENT_EX) $(SERVER_EX) $(CLIENT_EX_BONUS) $(SERVER_EX_BONUS)
	@echo "fclean ✔️"
re: fclean all
