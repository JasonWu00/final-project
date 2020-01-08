# Project Name:

# Members:
Jason Wu, Julian Wong (period 4)

# Broad description:

# Libraries:
SDL2:
enter `sudo apt-get install libsdl2-2.0` and `sudo apt-get install libsdl2-dev`
into the command line.
The SDL2 library should be installed for the computer once this is done.
This procedure can take a bit of time.

# Instructions to use the project:

# Proposal for the final project (APPROVED)

**People in the group**: Jason Wu, Julian Wong

**Project description**:

The project that we will be building is a simple version of the
Battleship game. The current plan calls for a Player vs Computer
(hereby referred to as Player vs Bot) mode and a Player vs Player mode.

We will be using the SDL library for this project.

**User Interface**:

The user interface would utilize SDL to create a new window, in
which the Battleship gameplay will occur. The user will be shown
a menu, which will prompt them to initiate a game of either Player
vs Bot or Player vs Player or exit the game.

Once the user selects either gamemode, the window will update with a
pair of coordinate grids (one for the user's playing field and one to
represent the enemy's playing field).

In either gamemode, both players start by placing down their "ships"
in the coordinate grid for them. Then, there will be a series of turns
where each player clicks on the coordinate grid for the enemy to try
to hit enemy ships. The game ends when one player had all their ships
sunk (by being hit in every grid space it occupies) or pressed a
surrender button (which will be included in a corner of the screen).

Once a game ends, the user will be sent back to the menu.

Notes: the user will be able to rotate their ships during placing time
by right clicking. The grid coordinate where the user clicks to place a
ship will not be where the center of the ship is; rather, it will be
where the head of the ship is at. This will be made clear to the users
by means of helpful tips included in the main menu.

**Technical Design**:

Since the project would be using SDL, and since the coordinate grids and
ships are best displayed as actual images in the window, we will have to
accumulate image sprites of things such as the grid, ships, hit/miss
markers, main menu and surrender buttons, etc, and then "open" them
into the window where the Battleship game will occur. And when switching
from the main menu to one of the two game modes and back, the images from
the former will have to be closed and the images for the latter opened.
(Working w/ files)

In a Player vs Player game, the devices of the two players will have
to send information to each other (example: the grid coordinate of the
shot fired, and a response of whether the shot was a hit or miss) via
networking. Since we are not yet familiarized with networking, Player
vs Player mode is expected to take more dev time than Player vs Bot.
(Networking)

To allow for multiple sessions of Battleship to be played back to back
without re-running the file, a child instance will be made for every
Battleship game. Once a game ends, the child ends and the game returns
to the "main menu", or the parent, and awaits the players to either
start another game (which makes a child) or exit the game (which ends
the parent). (Processes)

**Responsibilities**:

The project would likely consist of the following features: menu,
networking between machines (for Player vs Player), formatting of the
game screen (for both game modes), "bot" actions (for Player vs Bot),
and basic SDL. I am expecting to handle networking and formatting,
while Julian would be handling the menu and basic SDL. The coding of
the "bot" actions will be split between us two.

**Timeline**:

* January 2nd: Proposals due.
* January 3rd: Additional notes given in form of GitHub issue.
* (approx) January 6th: Approval of proposal (after revision).
* By January 6th: Understand the parts of SDL needed, acquire sprites.
* By January 7th: Begin actual coding. Make a menu for the game.
* By January 8th: Get started on PvP (+ forks and networking).
* (Expecting a lot of time for PvP mode, since networking is involved).
* By January 13th: Get started on PvBot mode. Should take a bit less time.
* By January 15th: finish both game modes, polish game, add quality of life features.
* January 17th: Project due.
