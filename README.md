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

The game will require the use of fork() to create child instances.
These child instances will carry out parts of the game, such as the
combat encounters between the player and randomly generated enemies
or the "shop" to purchase in-game upgrades in between encounters.

The user will be able to "save" their characters as well as their
progression in the game so that they can revisit the game at a later
time. The current plan includes both a method to save into a text file
and a method to save directly into system memory. The former allows
for saves to be ported from device to device, the latter
