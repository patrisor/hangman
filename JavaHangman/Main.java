/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    Main.java                                          :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: patrisor <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2019/05/26 10:54:20 by patrisor          #+#    #+#              */
/*    Updated: 2019/05/26 10:54:20 by patrisor         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

import java.util.*;
import java.io.*;

class Main 
{
	static String USAGE = "usage: java Main.java wordFile.txt";
	static List<String> easyList; // more than, equal to 4; less than, equal to 6
	static List<String> mediumList; // more than, equal to 7; less than, equal to 9
	static List<String> hardList; // More than or equal to 10

	/*
	 * Draws the correct image of the hangman, based on the current state of guesses
	 */
	public static void drawHangman(int guesses)
	{
		if (guesses == 0)
			System.out.println("  +---+\n" + "      |\n" + "      |\n" + 
					"      |\n" + "      |\n" + "      |\n" + "=========");
		if (guesses == 1)
			System.out.println("  +---+\n" + "      |\n" + "      |\n" +
					"  O   |\n" + "      |\n" + "      |\n" + "=========");
		if (guesses == 2)
			System.out.println("  +---+\n" + "      |\n" + "      |\n" +
					"  O   |\n" + "  |   |\n" + "      |\n" + "=========");
		if (guesses == 3)
			System.out.println("  +---+\n" + "      |\n" + "      |\n" +
					"  O   |\n" + " /|   |\n" + "      |\n" + "=========");
		if (guesses == 4)
			System.out.println("  +---+\n" + "      |\n" + "      |\n" +
					"  O   |\n" + " /|\\  |\n" + "      |\n" + "=========");
		if (guesses == 5)
			System.out.println("  +---+\n" + "      |\n" + "      |\n" +
					"  O   |\n" + " /|\\  |\n" + " /    |\n" + "=========");
		if (guesses == 6)
			System.out.println("  +---+\n" + "      |\n" + "      |\n" +
					"  O   |\n" + " /|\\  |\n" + " / \\  |\n" + "=========");
		if (guesses == 7)
			System.out.println("  +---+\n" + "  |   |\n" + "  O   |\n" + 
					" /|\\  |\n" + " / \\  |\n" + "      |\n" + "=========");
	}

	/*
	 * Removes whitespace from hangman gameState
	 */
	public static StringBuilder compress(StringBuilder oldString)
	{
		StringBuilder newString = new StringBuilder("");
		for (int i = 0; i < oldString.length(); i++)
			if (i % 2 == 0)
				newString.append(String.valueOf(oldString.charAt(i)));
		return (newString);
	}

	/*
	 * Logs every character already guessed and compares it to new guesses; 
	 * returns true if already guessed, and false otherwise
	 */
	public static boolean alreadyGuessed(String response, List<String> guessedList)
	{
		for (String element : guessedList)
			if (element.equals(response) == true)
				return (true);
		return (false); // not already guess
	}

	/*
	 * Creates and updates a game state, based on the word passed as a parameter;
	 * calls the draw function every time a character is incorrectly guessed;
	 * logs every character previously guessed
	 */
	public static void engine(String gameWord)
	{
		int				i;
		int				hit;
		int				guesses;
		StringBuilder	state;
		List<String>	guessedList;

		System.out.println("Your word has been chosen!");
		state = new StringBuilder("");
		i = -1;
		while (++i < gameWord.length())
			state.append("_ ");
		try {
			guesses = 0;
			guessedList = new ArrayList<String>();
			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
			while (true) {
				System.out.println("\nGuess a character!\n" + state);
				String response = input.readLine();
				if (alreadyGuessed(response, guessedList) == true) {
					System.out.println("You already guessed that! Try again!");
					continue;
				}
				i = 0;
				hit = 0;
				guessedList.add(response);
				for (; i < gameWord.length(); i++) {
					if (response.charAt(0) == gameWord.charAt(i)) {
						hit++;
						state.setCharAt(i * 2, gameWord.charAt(i));
					}
				}
				if (hit == 0) {
					drawHangman(guesses);
					guesses++;
				}
				if (compress(state).toString().equals(gameWord) == true) {
					System.out.println("You guessed the word, " + gameWord + 
							" with " + Integer.toString(8 - guesses) + " guess(es) left!");
					break ;
				}
				if (guesses == 8)
				{
					System.out.println("You did not guess the word, " + gameWord);
					break ;
				}
			}
		}
		catch(IOException e)
		{ e.printStackTrace(); }
	}

	/*
	 * Get a random word from a list passed as parameter
	 */
	public static String getRandomWord(List<String> list)
	{
		Random randomGenerator = new Random();
		int randomInt = randomGenerator.nextInt(list.size() - 1);
		return(list.get(randomInt));
	}
	
	/*
	 * Introduction to game, which prompts user to choose which difficult they want
	 * associates their response with the correct list 
	 */
	public static List<String> getList()
	{
		String	response;
		List<String> chosenList;

		System.out.println("Welcome to Hangman!");
		// Prompt User for Input
		System.out.println("Choose your difficulty level:\nEASY\tMEDIUM\tHARD");
		chosenList = new ArrayList<String>();
		try
		{
			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
			while (true)
			{
				response = input.readLine();
				// If Easy was chosen, a word lower than len three is picked
				if (response.equals("EASY") == true) {
					System.out.println("EASY was chosen");
					chosenList = easyList;
					break ;
				}
				else if (response.equals("MEDIUM") == true) {
					System.out.println("MEDIUM was chosen");
					chosenList = mediumList;;
					break ;
				}
				else if (response.equals("HARD") == true) {
					System.out.println("HARD was chosen");
					chosenList = hardList;
					break ;
				}
				else
					System.out.println("Incorrect Response. Try Again.");
			}
		}
		catch(IOException e)
		{ e.printStackTrace(); }
		return (chosenList);
	}
	
	/*
	 * Reads a file passed as parameter, and separates the words into
	 * 4 different lists: EASY, MEDIUM, HARD, EXTREME
	 */
	public static void parseFile(String filename)
	{
		// Create new lists
		easyList = new ArrayList<String>();
		mediumList = new ArrayList<String>();
		hardList = new ArrayList<String>();
		// Choose a word from file of 100,000 words
		try
		{
			FileReader fr = new FileReader(filename);
			BufferedReader br = new BufferedReader(fr);
			String line = br.readLine();
			while (line != null)
			{
				// Store into Array(s) based on size of word
				if (line.length() <= 3) {
					line = br.readLine();
					continue ; // Ignores word
				}
				if (line.length() >= 4 && line.length() <= 6)
					easyList.add(line);
				if (line.length() >= 7 && line.length() <= 9)
					mediumList.add(line);
				if (line.length() >= 10)
					hardList.add(line);
				line = br.readLine();
			}
			br.close();
			fr.close();
		}
		catch(IOException e)
		{ e.printStackTrace(); }
	}

	// TODO: Delete Test Function
	private static void putList(List<String> list)
	{
		for (String element : list) {
			System.out.println(element);
		}
	}
	
	public static void main(String[] args) 
	{
		// Error Check
		if (args.length != 1) {
			System.out.println(USAGE);
			System.exit(-1);
		}
		// Reads a file passed as input, and separates the words into
		// 4 different lists: EASY, MEDIUM, HARD, EXTREME
		parseFile(args[0]);
		// Get a list from file passed as parameter, then  
		// get a random word from a list passed as parameter
		engine(getRandomWord(getList()));
		System.exit(0);
	}
}
