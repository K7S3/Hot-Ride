# README FLYING WHEEL(JETPACK JOYRIDE CLONE)

## How to run the game

### COMPILE

    cmake CMakeLists.txt
    make

### RUN THE EXECUTABLE

    ./graphics_asgn1

## CONTROLS
    The user can play by keyboard.
    Zooming and done using the mouse.

|Keyboard| Controls|
|-----|----|
|KEY 	|ACTION|
|Up arrow| 	Jump|
|Down arrow |	Nothing|
|Left arrow |	Move left|
|Right arrow |	Move right|
|ESC |	Quit|
|w 	|Pan up|
|a 	|Pan left|
|s 	|Pan down|
|d 	|Pan right|
|x | Throw water balloon|

Mouse Controls

    Scroll up to Zoom in.
    Scroll down to Zoom out.
    Mouse click and drag for panning when screen is zoomed.
## RULES 

### Basic
    The player has three lives.
    Enemies, powerups, coins appear at random distances and heights.
    Presence of semicircular ring which controls the motion.
    Ablility to throw water ballons and extinguish firelines (follows a projectile trajectory)
    Presence of Magnets that alters motion.

### Powerups

|POWERUP | DESCRIPTION|
|---|--|
| Shieldup | Provides a shield that can cut across enemies and lasts for 6 seconds|
| Speedups | Player moves 4 times faster and lasts for 4 seconds|
| Lifeups | Provides one extra life|

### ENEMIES

|ENEMY| DESCRIPTION|
|--|--|
|Firelines | Simeple firelines present at various heights |
|Firebeams | Activates when player is near it and moves vertically|
|Boomerang(SMART) | Aimed at player, follows a horizontal U trajectory |
| Dragon | Moves up and down casting fire. Has 2 lives |
### Scoring 

    Each coin has a random score and is present at a random height.
    Points are deducted for every life lost depending on the enemy.
|ENEMY| POINTS DEDUCTED|
|--|--|
|Firelines | 50 |
|Firebeams | 30 |
|Boomerang | 20 |
| Dragon | 100 |



  