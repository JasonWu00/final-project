# Proposal for the final project

**People in the group**: Jason Wu, Julian Wong

**Project description**:

The project that we will be building is an RPG game.
We have not yet decided on the plot for the RPG game, if any,
but it is expected to have a system of battles against enemies,
levels (and associated perks), upgrades for in-game currency,
and more features.

**User Interface**:

The user interface would be centered around the command line.
The program will print out relevant information regard the current
game state, then prompt the user to make a choice. This may be
subject to change as the project develops.

**Technical Design**:

Everything below this is not 100% certain and might change.

The game will require the use of fork() to create child instances.
These child instances will carry out parts of the game, such as the
combat encounters between the player and randomly generated enemies
or the "shop" to purchase in-game upgrades in between encounters.
(PROCESSES)

The user will be able to "save" their characters as well as their
progression in the game so that they can revisit the game at a later
time. The current plan includes a method to save into either a text
file or directly into system memory. The former allows for saves to
be ported from device to device, the latter reduces the need to
hassle with files that may be misplaced. (WORKING WITH FILES)

The different "modes" for the game would include a quick match mode
(where the player verses off against a bot enemy), story mode (the
main gamemode), and a 1v1 mode (where two different players face off
against each other in a turn based combat). The 1v1 mode would make
use of semaphores and either a section of shared memory or a file,
so that only one player can "move", or update the game state by
making edits to the memory / file. (SEMAPHORE)

Timeline:

* January 2nd: Proposals due
* (approx) January 3rd: approval of proposal and/or additional notes
* (insert events here)
* January 17th: Project due
