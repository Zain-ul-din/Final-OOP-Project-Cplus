# Demo

![2022-10-15_14-32-41_AdobeExpress](https://user-images.githubusercontent.com/78583049/195980076-53a10a6c-a86b-4b0e-ba2f-4bb9aa209eaf.gif)

---

- 👋 Hi, I’m Zain-ul-din
- Rank : " Student "


 >  I like my code to be elegant and efficient. The logic should be straightforward to make it hard for bugs to hide, the dependencies minimal to
 >  ease maintenance, error handling completeaccording  to an articulated strategy, and performance close tooptimal so as not to temptpeople to 
 >  make the code messy with unprincipled optimizations. Clean code does one thing well.

 # USAGE
 
 > Clone Repo and compile `index.cpp`

# DOCS

# Tic Tac Toc Game in C++

> A Tic Tac Toc game implemented in C++. This game uses the ```C++11``` standard.

### Requirements

This game requires a ```C++11``` compliant compiler. You can check if your compiler supports ```C++11``` by checking if ```__cplusplus``` is defined as ```201103L``` or greater.

### Included Libraries

- ```<iostream>``` for standard input and output.
- ```<string>``` for standard string operations.
- ```<vector>``` for dynamic arrays.
- ```<algorithm>``` for the standard algorithm library.
- ```<cmath>``` for math functions.
- ```<windows.```h> for Windows API functions such as keyboard button clicks.
- ```<conio.```h> for the getch() function to get a character from the keyboard.
- ```<thread>``` for C++11 multi-threading and thread sleep.
- ```<chrono>``` for C++ system time.
- ```<functional>``` for C++11 functions.


# Classes

- ```Event:``` a custom event handler class that triggers an action when something happens and can have multiple subscribers
- ```InputManager:``` a class that manages input from the user
- ```GameRenderer:``` a class that renders the game map, player UI, etc.
- ```GameManager:``` a class that manages the game state and logic


### Macros

- ```DEFAULT_BOX:``` the character to use for an empty box in the game map
- ```PLAYER1_BOX:``` the character to use for player 1's box in the game map
- ```PLAYER2_BOX:``` the character to use for player 2's box in the game map
- ```CURSOR:``` the character to use for the cursor in the game map
- ```_CH_:``` a macro for calling the getch() function
- ```CLS:``` a macro for calling the clearScreen() function

### Enums

- ```PlayerTurn:``` an enum to represent the current player's turn

### Usage

To use this game, compile and run the code using a C++11 compliant compiler. The game will display the game map and allow the user to move the cursor and fill boxes using the keyboard. The game ends when a player wins or it ends in a draw.

I hope this helps! Let me know if you have any other questions.
