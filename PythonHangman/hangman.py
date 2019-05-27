from random import randint

def hangman():
  words = [line.rstrip('\n') for line in open('words.txt', 'r')]
  game_word = list(words[randint(0, len(words) - 1)])
  lives = len(game_word) * 2
  turn = 0
  underscores = list("_ " * len(game_word))
  g = True
  while g:
    print("Lives left: " + str(lives))
    print("".join(underscores))
    char = input("Please input a character\n") 
    i = 0
    while i < len(game_word):
      if char == game_word[i]:
        underscores[i * 2] = char
      i += 1
    if i == len(game_word):
      lives -= 1
    # TODO: Checker if its right or not 
    if lives == 0:
      break
    turn +=1 
  print("Game Over!\n")

def main(): 
  hangman()

if __name__ == "__main__":
  main()
