# Presentor details:
- Name: Uriel Shapiro
- Last digits of ID: 9745
- Email: uriel1999@gmail.com


# Catan Game Documentation

This document provides a brief description of each function within the `Catan` game:

To make the demo executable run:
```bash
make Demo
```

To make and run the test executable, run:
```bash
make Test
```

To make the main game, run:
```bash
make Game
```

### Game logic:
The Catan class manages the overall gameplay for a game of Catan. It initializes the game with players, controls the game board, and handles the main game mechanics such as rolling dice, buying and using development cards, and placing initial game pieces. It also tracks game progress, checks for victory conditions, and maintains player statistics and turns. The class ensures the correct execution of game rules and provides the necessary interactions between players and the game board.

## Catan Class

### Constructor
- Initializes a new game instance with three players. Prints a message indicating the start of the game and the starting player.

### `getBoard`
- Returns a pointer to the shared `Board` instance used in the game.

### `StartingGame`
- Starts the game by placing roads and villages based on the provided placements for each player. Throws an error if the input sizes are incorrect.

### `rollDice`
- Rolls the dice for the current player, checks for special conditions (like rolling a 7, which triggers card discarding), and distributes resources accordingly.

### `buyDevelopmentCard`
- Allows the current player to purchase a development card if they have sufficient resources. Resources are deducted, and a random card is added to the player's collection.

### `use_development_card`
- Enables the use of a purchased development card by the current player. The effect of the card depends on its type, such as building roads, taking resources from other players, etc.

### `check_winner`
- Checks if any player has reached the victory point threshold (10 points). If so, declares the winner and returns `true`.

### `check_largest_army`
- Determines if the current player has the largest army based on the number of Knight cards. Updates the largest army requirement if necessary.

### `GameCheck`
- Performs a check to see if the game has ended due to a win condition or reaching the largest army requirement. Moves to the next player if not ended.

### `print_players_stats`
- Prints statistics for all players involved in the game.

### `get_players`
- Returns a pointer to the array of `Player` objects participating in the game.

### `get_turn`
- Returns the index of the current player's turn.

### Destructor (`~Catan`)
- Cleans up by deleting the dynamically allocated `Board` object.

## Player Class

### Constructor

Initializes a new `Player` object with the specified player name and sets default values for various attributes such as ID, resource amounts, cards, victory points, and building status.


### Destructor

Responsible for cleaning up dynamically allocated `Buildable` objects stored in the `buildings` vector to prevent memory leaks.


### `change_victory_points`

Adjusts the player's victory points by a specified amount, incorporating validation to ensure victory points do not exceed 2 per turn and remain non-negative. Throws an exception for invalid operations.


### `get_victory_points`

Retrieves the current number of victory points held by the player.


### `rollDice`

Simulates rolling two six-sided dice and returns the sum, providing a mechanism for generating random numbers in gameplay scenarios.


### `get_name`

Retrieves the player's name, facilitating identification within the game.


### `get_id`

Obtains the unique identifier assigned to the player, useful for tracking and referencing players.


### `placeSettlement`

Places a settlement or village/city on the game board, requiring specific resources and validating placement against game rules.


### `placeRoad`

Constructs a road connecting two vertices on the game board, checking for valid placement and sufficient resources.


### `game_start_placement`

Performs initial placements of roads and settlements at the start of the game, based on the provided placements.

### `check_valid_resources`

Checks if the player has enough of a specified resource.

### `get_development_cards`

Returns a reference to the vector containing the player's development cards.
Notice that it is changeable.

### `set_largest_army`

Updates the player's status regarding having the largest army, adjusting victory points accordingly.

### `rollDice`

Simulates rolling two six-sided dice and returns the sum of the results.

### `get_name`

Returns the player's name.

### `get_id`

Returns the unique identifier of the player.

### `trade - DevelopmentCard`
Allows the current player to trade a set of development cards with another player (`p`). The current player receives cards from the other player.
Returns `true` if the trade was successful, `false` otherwise.

### `trade - ResourceCard`

Enables the current player to trade a set of resource cards with another player (`p`). The current player receives cards from the other player.
Returns `true` if the trade was successful, `false` otherwise.

### `get_total_cards`

Returns the total number of cards (resource and development) currently held by the player.

### `discard_half_cards`

Discards half of the player's cards if the total number of cards exceeds 7. This action is part of the game's rules when a dice roll result is 7.

###  `print_stats`

Prints detailed statistics about the current player, including resources, total cards, victory points, and whether the player has the largest army.

### `get_is_largest_army`

Checks if the current player has the largest army in the game.


##  Board Class

### Constructor

- Initializes the board by creating instances of `Edge`, `Vertex`, and `Tile`.
- Uses a singleton pattern to ensure only one instance of the `Board` exists.
- Iterates through predefined constants to create vertices representing different types of terrain (sea, mountain, pastures, hill, forest, field, desert).
- Creates edges between these vertices to form the basic structure of the map.
- Groups these vertices and edges into tiles, each representing a section of the map with specific properties.

### Destructor

- Cleans up dynamically allocated memory for vertices, edges, and tiles to prevent memory leaks.
- Resets the `instance` pointer to `nullptr`.

### Singleton Pattern (`get_instance()`)

- Ensures that only one instance of the `Board` class exists throughout the application.
- Returns the existing instance if it exists; otherwise, creates a new instance.

  
### `valid_settlement_placement`

- Checks if a settlement can be placed on a given vertex based on adjacency rules:
- The vertex must be adjacent to another vertex with a building of the same player.
- There must be a road connecting the vertex to a neighboring vertex with a building of the same player.

### `valid_road_placement`

- Validates the placement of a road on a given edge:
  - The edge must not already be taken.
  - The road must connect two vertices, either both with buildings of the same player or one with a building and the other with a road of the same player.

### Getter Methods

- `get_tiles()`: Returns a vector of pointers to all `Tile` objects on the board.
- `get_edges()`: Returns a vector of pointers to all `Edge` objects on the board.
- `get_vertices()`: Returns a vector of pointers to all `Vertex` objects on the board.



