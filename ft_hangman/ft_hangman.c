/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hangman.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:58:38 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/26 17:06:47 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define USAGE "usage: ./ft_hangman wordfile"
#define PROMPT "Guess a character!"

/* TODO: Optimize for Norminette
 * Function creates 7 versions of a hangman ascii art
 * NOTE: Make sure to free address right after this is called
 */
char	*robin_williams(int	state)
{
	char	*stick;

	stick = (char *)malloc(sizeof(char) * 57);
	if (stick == NULL)
		return (NULL);
	if (state == 0)
		stick = "  +---+\n  |   |\n      |\n"
			"      |\n      |\n      |\n=========";
	else if (state == 1)
		stick = "  +---+\n  |   |\n  O   |\n"
			"      |\n      |\n      |\n=========";
	else if (state == 2)
		stick = "  +---+\n  |   |\n  O   |\n"
			"  |   |\n      |\n      |\n=========";
	else if (state == 3)
		stick = "  +---+\n  |   |\n  O   |\n"
			" /|   |\n      |\n      |\n=========";
	else if (state == 4)
		stick = "  +---+\n  |   |\n  O   |\n"
			" /|\\  |\n      |\n      |\n=========";
	else if (state == 5)
		stick = "  +---+\n  |   |\n  O   |\n"
			" /|\\  |\n /    |\n      |\n=========";
	else
		stick = "  +---+\n  |   |\n  O   |\n"
			" /|\\  |\n / \\  |\n      |\n=========";
	return (stick);
}

/*
 * Compresses our game state. For example, it would compress 'h e l l o' to 'hello'.
 * NOTE: Make sure to free address right after this is called
 */
char	*compress(char *underscores)
{
	int		i;
	int		tmp;
	char	*out;

	out = (char *)malloc(sizeof(char) * (int)ft_strlen(underscores) / 2);
	tmp = -1;
	i = -1;
	while (underscores[++i])
		if (i % 2 == 0)
			out[++tmp] = underscores[i];
	return (out);
}

/*
 * TODO:
 */
void	engine(char *game_word, char *underscores)
{
	int		i;
	//int		max;
	int		guesses;
	char    user_input;
	char	*compressed;

	// max = (int)ft_strlen(game_word) * 2;
	guesses = 0;
	// Game Engine
	while (1)
	{
		// Resets user input
		user_input = '\0';
		// Updates state of the game
		ft_putstr(underscores);
		// Prompt
		ft_putendl(PROMPT);
		// User input from STDIN (STDIN_FILENO = 0)
		read(STDIN_FILENO, &user_input, 2);
		// TODO: Error Check User if they inputted more than one character
		// TODO: Account for already picked characters
		i = 0;
		// Iterate game word
		while (game_word[i])
		{
			// Check if character is equal to a character in gameWord
			if (game_word[i] == user_input)
				// Update character in underscores if it is equal
				underscores[i * 2] = user_input;
			// break if it read the whole word
			if (i == (int)ft_strlen(game_word))
				break ;
			i++;
		}
		/* TODO: Fix Guesses
		guesses++;
		ft_putendl(ft_strjoin("Guesses: ", ft_itoa(guesses))); */

		// Compresses our game state. For example, it would compress 'h e l l o' to 'hello'.
		compressed = compress(underscores);
		if (ft_strcmp(game_word, compressed) == 0)
		{
			ft_putendl(ft_strjoin("Congratulations! You guessed the word ", game_word));
			free(compressed);
			break ;
		}
		free(compressed);

		/* TODO: Convert this into a function where you pass in number of guesses
		 * to get back a different prompt
		// Checks if guesses reached Max
		if (guesses == max)
		{
			ft_putendl(ft_strjoin("Game Over! The word was ", game_word));
			break ;
		}
		// If nothing was found, Subtract Guesses Left
		else
			ft_putendl(ft_strjoin("Guesses Left: ",\
						ft_strjoin(ft_itoa(max - guesses), "\n")));
		*/
	}
}

/*
 * Reads word chosen, manipulates the underscores game state based on game word, then
 * strcpy both to become stored in our game engine
 */
void	ft_hangman(char *word)
{ 
	int		i;
	char	*temp;
	char	game_word[(int)ft_strlen(word)];
	char	underscores[(int)ft_strlen(word) * 2];

	temp = "";
	// Stores word into one which will be manipulated
	ft_strcpy(game_word, word);
	// Changes last value to a null value
	// game_word[(int)ft_strlen(word)] = '\0';
	// append "_ ", underscores, ft_strlen amount of times
	i = -1;
	while (++i < (int)ft_strlen(game_word))
		temp = ft_strjoin(temp, "_ ");
	// underscores which will be manipulated
	ft_strcpy(underscores, temp);
	// Changes the last value of underscores to a '\n', instead of ' '
	underscores[ft_strlen(underscores) - 1] = '\n';
	// 
	engine(game_word, underscores);
}

/*
 * Seeds, then generates random int between 0 and length of lines in map, minus one
 */
char	*random_word(char **map, int lines)
{
	// Seed random
	srand(time(NULL));
	// Generates random int between 0 and length of lines in map, minus one
	return (map[rand() % lines]);
} 

/* 
 * Optional Function which reads a file taken as input, separates every value into an array,
 * then randomly chooses a word to be stored in our ft_hangman function
 */
char	*parse_rand(int fd)
{
	int		lines;
	char	*rand;
	char	*word;
	char	**map;
	char	*tmp;

	lines = 0;
	tmp = "";
	// Feedbacks the user
	ft_putendl("Picking random word from file...");
	// Reads every line of file
	while (get_next_line(fd, &word) == 1)
	{
		// Append lines on top of each other
		tmp = ft_strjoin(tmp, ft_strjoin(word, "\n"));
		lines++;
	}	
	// Allocate memory for map
	map = (char **)malloc(sizeof(char *) * lines);
	if (map == NULL)
		return (NULL); 
	// Stores tmp (word1\nword2\nword3\n...) into map
	map = ft_strsplit(tmp, '\n');
	// Picks a random word read from map
	rand = random_word(map, lines);	
	// Closes File
	close(fd);
	// Free map address once you are finished with it
	free(map);
	return (rand);
}

int		main(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		ft_putstr(USAGE);
		return (-1);
	}
	// Opens a file
	fd = open(argv[1], O_RDONLY);
	// Error Check
	if (fd < 0)
		return (-1);
	// Pass our randomly generated word into our hangman engine
	ft_hangman(parse_rand(fd));		
	return (0);
}
