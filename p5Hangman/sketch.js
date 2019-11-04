var gameWord;
var words;
var gameState;
var incorrectBytes;
var incorrectGuesses;

/****************************************/
/**************** INTRO *****************/
/****************************************/

function preload() {
  words = loadStrings("words.txt");
}

function initGameState() {
  out = "";
  for (var i = 0; i < gameWord.length; i++)
    out += "_ ";
  return(out);
}

function setup() {
  createCanvas(400, 400);
  fill(0, 0, 0);
  noStroke();
  gameWord = random(words);
  gameState = initGameState();
  incorrectBytes = "";
  incorrectGuesses = 0;
}

/****************************************/
/************** AUXILIARY ***************/
/****************************************/

function replaceAt(s, n, t) {
    return s.substring(0, n) + t + s.substring(n + 1);
}

function drawHangman(num) {
  if (num == 1)
    rect(100, 100, width / 2, height / 2);
}

/****************************************/
/***************** MAIN *****************/
/****************************************/

function draw() {
  background('#fae');
  incorrectGuesses = incorrectBytes.length / 3;
  textSize(32);
  text(gameState, 0, (height - 60));
  textSize(16);
  text("Incorrect: ", 0, (height - 35));
  text(incorrectBytes, 0, (height - 10));
}

function keyPressed() {
  console.log(gameWord);
  console.log(incorrectGuesses);
  
  var incorrect = 0;
  var correct = 0;
  for (var i = 0; i < gameWord.length; i++) {
    if (gameWord[i] == key) {
      gameState = replaceAt(gameState, i * 2, key);
      correct++;
    } else
      incorrect++;
  }
  if (correct == 0 && incorrect > 0) {
    var hit = 0;
    for (var i = 0; i < incorrectBytes.length; i++)
      if (incorrectBytes[i] == key)
        hit++;
    if (hit == 0) {
      incorrectBytes += (key + ", ")
      drawHangman(incorrectGuesses);
    }
  }
  return false; 
}
