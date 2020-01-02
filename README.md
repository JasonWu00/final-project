# Proposal for the final project

Note: This proposal is likely not going to resemble the final
product and significant changes may occur.

**People in the group**: Jason Wu, Julian Wong

**Project description**:

The project that we will be building is a simple version of the
Battleship game. The current plan calls for a Player vs Computer
mode and a Player vs Player mode. We are expecting to use the SDL
library for this project.

**User Interface**:

The user interface would utilize SDL to create a new window, upon
which the Battleship gameplay will occur. In either gamemode, both
players start by placing down their "ships" in the window. Then,
there will be a series of turns where each player clicks on a section
of the screen designated for "the enemy's board" to try to hit enemy
ships. The game ends when one player has all their ships hit or
presses a surrender button (which will be included in a corner of
the screen).

**Technical Design**:

The state of the game at any moment will be saved in either a file
or a chunk of shared memory (in the case of a Player vs AI game), so
that the user may return to the game later. (Shared Mem or Files)

Said file or shared mem could be passed between two computers engaged
in a Player vs Player game as a method of transmitting moves. Since we
are not yet familiarized with networking, this part may be subject to
significant change. (Networking(?))

In the event that a Player vs AI game is in progress, a semaphore can
be implemented to ensure that only 1 player is interacting with the
current state of the game. It would be unfortunate if both the "bot" 
and the player tried to move at the same time and messed up the game.
(Semaphore)

To allow for multiple sessions of Battleship to be played without
re-running the executable file, a child instance may be required per
Battleship game. Once a game ends, the child ends and the game returns
to the "main menu", or the parent, and awaits the players to either
start another game or exit the game. (Processes)

**Responsibilities**:

The project would likely consist of the following features: menu,
networking between machines (for PvP) (not final), formatting of
the game screen (for either game mode), "bot" actions (for PvBot),
and basic SDL. I am expecting to handle networking and formatting,
while Julian would be handling the menu and basic SDL. The coding
of the "bot" actions may be split between us two.

**Timeline**:

* January 2nd: Proposals due.
* (approx) January 3rd: approval of proposal and/or additional notes.
* By January 6th: Understand the parts of SDL needed, set up menu, acquire sprites.
* By January 8th: Get started on PvP (+ forks and possibly networking).
* (Expecting a lot of time for PvP mode, since networking is involved).
* By January 13th: Get started on PvBot mode. Should take a bit less time.
* By January 15th: finish both game modes, polish game, add quality of life features.
* January 17th: Project due.
