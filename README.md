Donkey Kong Game (C++)
This repository contains an implementation of the classic Donkey Kong game in C++ for a console environment. The game is designed to simulate the arcade version, with a few custom additions such as ghosts, hammers, and file-based level loading.


Game Overview
The objective of this project is to recreate the classic Donkey Kong game, where Mario must avoid falling barrels, climb ladders, and reach Pauline while avoiding enemies, like ghosts. The game runs on a Windows console with a resolution of 80x25 characters.

Game Elements:
Mario (Hero): The player character, represented by @.
Donkey Kong: The antagonist, represented by &.
Barrels: Thrown by Donkey Kong, represented by O.
Floors: Represented by <, >, or =, indicating the direction of barrel movement.
Ladder: Represented by H.
Pauline: Mario's objective, represented by $.
Ghosts: Enemies that wander on the floors, represented by x (non-climbing) and X (climbing).
Features
Basic Gameplay: Move Mario with the keys a, d, w, x, s for left, right, jump, down, and stay.
Lives & Score: Mario has 3 lives, and the score is tracked for each level.
Ladders & Jumping: Mario can climb ladders and jump over obstacles.
Barrel Mechanics: Barrels fall down and move horizontally, causing damage if they hit Mario.
Ghosts & Hammers (Bonus): Ghosts can be defeated by using a hammer. Ghosts can also change direction randomly on floors.
File-based Level Loading (Bonus): Levels can be loaded from text files, allowing for custom levels.

Movement:
Use a or A to move left.
Use d or D to move right.
Use w or W to jump up.
Use x or X to move down.
Use s or S to stay in place.
Bonus Features
Color Support: Option to toggle colors on/off in the game.
Ghosts with Random Movements: Ghosts wander on the floor with a 95% chance of continuing their direction and 5% of changing direction.
Hammer: Mario can use a hammer to destroy barrels and kill ghosts.

Level Loading from Files: Custom levels can be loaded from .screen files. The game supports dkong_*.screen files for custom layouts.
File Formats
Screen Files (*.screen):
These text files define the layout of the level with specific characters representing different elements:

Q: Walls/Boundaries.
&: Donkey Kong.
@: Mario.
$: Pauline.
=, <, >: Floor directions.
H: Ladder.
x: Ghost.
p: Hammer.

Steps Files (*.steps):
These files track the movements and actions of game entities (e.g., Mario, barrels) during gameplay.

Result Files (*.result):
These files record the results of a game session, including Mario’s lives lost, level completion, and score.

Usage
Installation
Prerequisites:
Visual Studio 2022 or later.
Standard C++ libraries.
Windows environment with console screen size 80x25.
Steps:
Clone the repository: 
https://github.com/pamnati592/Donkey-Kong-Game-CPP

Open the solution (.sln) file in Visual Studio.
Build and run the project using Visual Studio.

Running from Visual Studio:
You can also run the game with these parameters directly from Visual Studio:

Open the project in Visual Studio.
Right-click on the project and select Properties.
In the Debugging section, find the Command Arguments field.
Enter the desired command-line arguments (-load, -save, and optionally -silent).
Example for loading the game: -load.
Example for saving the game: -save.
Save the changes and run the project.

Running from Command Line:
You can run the game with specific parameters from the command line to load or save game states.

dkong.exe -load|-save [-silent]
Parameters:
-load: Loads a previously saved game state.
-save: Saves the current game state to a file.
-silent (Optional): Runs the game without printing output to the console (silent mode).
Examples:
Load a Saved Game: To load a previously saved game:

dkong.exe -load
This will load the most recent saved game state.

Save the Current Game: To save your current game:

dkong.exe -save
This will save the current game state.

Silent Mode: To load or save the game without displaying any output in the console:

dkong.exe -load -silent
or

dkong.exe -save -silent

