# The Lord of the Rings
## Project overview
This project is a command-line-based role-playing adventure game based on J.R.R. Tolkien's high-fantasy novel. The objective of the game is for the player to become the Ringbearer and destroy the One Ring in the fires of Mount Doom. The player starts at the bottom-left of a square gridded map and must navigate to the top-right where Mount Doom is located.
Along the way, the player will encounter various terrains (Wall, Grass, EmptyLand), collect items (Gem, Book, Medicine), and defeat monsters (Zombie, Warlock, DarkPriest). The player can choose to play as one of three roles (Warrior, Archer, Mage) each with unique characteristics and skills to defeat monsters.
The implementation of this game utilizes the principles of polymorphism and inheritance in OOP to bring the various elements of the game to life.

## Basic game concept
### Game UI
The UI of this game is shown below. This UI gets information of the game status by calling the functions implement in
other classes. Area out of the game map will display as "XXX" by the game UI.
![image](https://user-images.githubusercontent.com/45839865/218324880-754a7b3b-e492-466c-9a42-4c50900c2af3.png)

### Map Unit
The MapUnit is the basic abstraction of all elements on the game map. There are totally 9 types
of map units, which are summarized into three categories. Different map units have different
behaviors in the game. The hierarchy of the map unit is shown below:
![image](https://user-images.githubusercontent.com/45839865/218324986-fb76eb81-1a49-4244-b0ad-d309c70303a3.png)
