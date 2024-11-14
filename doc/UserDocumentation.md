**User
Documentation**

<a name="_page1_x72.00_y72.00"></a>Table of contents

## Table of Contents
1. [Getting Started](#getting-started)
   - [Prerequisites](#prerequisites)
   - [GCC Installation](#gcc-installation)
2. [Launch the Game](#launch-the-game)
3. [Rules](#rules)
   - [Objective](#objective)
   - [Game Setup](#game-setup)
   - [Game Flow](#game-flow)
      - [Turn Order](#turn-order)
      - [Tiles and Placement Rules](#tiles-and-placement-rules)
   - [Special Squares and Bonuses](#special-squares-and-bonuses)
   - [Game End and Scoring](#game-end-and-scoring)
      - [Final Round Option](#final-round-option)
      - [Determining the Winner](#determining-the-winner)
4. [Controls](#controls)


1. Getting<a name="_page2_x72.00_y333.83"></a> Started
2. Prerequisites
- <a name="_page2_x72.00_y393.54"></a>Linux (Fedora, Ubuntu, Debian, etc)
- GCC
2. GCC<a name="_page2_x72.00_y490.24"></a> Installation

Before installing GCC, update the package list to ensure you get the latest version of GCC available in your distribution's repositories.

- “sudo apt update” For Debian-based systems (Ubuntu, etc)
- “sudo yum update” For RHEL-based systems (CentOS, etc)
- “sudo dnf update” For Fedora

On Debian-based systems, use apt to install GCC:

- sudo apt install gcc
- sudo apt install g++

On CentOS/RHEL, use yumto install GCC:

- sudo yum install gcc
- sudo yum install gcc-c++

On Fedora, use dnf to install GCC:

- sudo dnf install gcc
- sudo dnf install gcc-c++
2. Launch<a name="_page3_x72.00_y263.24"></a> the game

Install the game folder on your computer > Open a terminal > Go to the game folder (cd <folder\_name>) > Type “make” > Type “./laying\_grass” > The game is launched

3. Rules
1. <a name="_page3_x72.00_y381.13"></a>Objective

<a name="_page3_x72.00_y426.29"></a>In "Laying Grass," players take turns placing grass tiles on a grid to expand their territory, aiming to create the largest continuous square territory by the end of the game. The player with the largest square territory wins. If there’s a tie, the player with the most grass squares in their territory wins.

2. Game<a name="_page3_x72.00_y536.98"></a> Setup
- **Players**: The game can be played by **2 to 9 players**.
- **Board Size**:
  - For **2-4 players**: a **20x20 grid**.
  - For **5-9 players**: a **30x30 grid**.
- **Player Customization**: Each player enters their name and chooses a color at the start.
- **Starting Tile**: Each player receives a **1x1 tile** to place as their starting location.
- **Tile Exchange Coupon**: Each player starts with **one tile exchange coupon** to use strategically.
3. Game<a name="_page4_x72.00_y72.00"></a> Flow
1. Turn<a name="_page4_x72.00_y94.51"></a> Order
- The order of play is randomized at the start.
- Players take turns placing grass tiles to expand their territories.
2. Tiles<a name="_page4_x72.00_y173.47"></a> and Placement Rules
- **Tile Queue**: Tiles come in a predetermined, but random, order. Players receive the **first tile in the queue** on their turn.
- **Tile Exchange**: Players may use a tile exchange coupon to pick any one tile from the **next five tiles in the queue**. After choosing, the next player receives the tile that follows the chosen one. Tiles passed over return to play in the same order once all tiles are used.
- **Placement Rules**:
  - Players must place their first tile **adjacent to their starting tile**.
  - Subsequent tiles must touch the existing tiles in the player’s territory on at least one side.
  - **No overlapping or touching other players' territories**.
  - Tiles can be **rotated or flipped** in any direction to fit.
- **Skipping a Turn**: If a tile cannot be legally placed, it is discarded and the player skips their turn.
4. Special<a name="_page4_x72.00_y418.99"></a> Squares and Bonuses

Special squares provide unique benefits and can only be activated by placing tiles adjacent to them on **all four cardinal sides (left, right, above, and below)**. Once activated, the square joins the player's territory.

- **Tile Exchange Square**: Grants the player **one additional tile exchange coupon**. There are approximately 1.5 of these squares per player, rounded up.
- **Stone Square**: Allows the player to place a **stone tile** on any empty space, blocking others from placing tiles on that spot. Removing a stone tile costs one tile exchange coupon. There are approximately 0.5 of these squares per player, rounded up.
- **Robbery Square**: Lets the player **take a tile from another player** and add it to their territory. There is one robbery square per player.

**Note**: Stone and robbery squares must be used immediately upon activation. Bonuses are randomly distributed at the beginning of the game and cannot be placed at board edges or near other bonuses. Players may cover bonus squares, which makes them inactive.

5. Game<a name="_page5_x72.00_y72.00"></a> End and Scoring

The game concludes after **nine rounds** (each player places nine tiles).

1. Final<a name="_page5_x72.00_y129.06"></a> Round Option
- At the end, players may use a tile exchange coupon to purchase a **1x1 grass tile** to place freely in their territory for an additional advantage.
2. Determining<a name="_page5_x72.00_y200.02"></a> the Winner
- The winner is the player with the **largest square territory** (e.g., 7x7).
- In the event of a tie, the player with the **highest number of grass tiles in their territory** wins.
4. Controls

<a name="_page5_x72.00_y300.07"></a>To make gameplay simple, players only need a few basic keys to play and place tiles:

- **Movement**: Use **Z, Q, S, D** keys (or **arrow keys**) to navigate the grid and menus.
- **Z / Up Arrow**: Move up
- **Q / Left Arrow**: Move left
- **S / Down Arrow**: Move down
- **D / Right Arrow**: Move right
- **Placing Tiles**: Press **Enter** to confirm and place the tile on the selected grid position.
