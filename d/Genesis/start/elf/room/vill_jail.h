/* 
 * Some standard definitions for the village jail.
 */

#define JAIL_NAT_SHORT "Inside the village jail"
#define JAIL_FOR_SHORT "Inside a stone house"

#define JAIL_NAT_LONG \
  "You're in a small stone room inside the village jail. The thick walls are "+\
  "bare, pale yellow stone, and "+\
  "all the windows have metal bars. The floor and ceiling is the same yellow " +\
  "stone as the walls, and all the doors are heavily reinforced.\n"
#define JAIL_FOR_LONG \
  "You're in a small stone room. The thick walls are "+\
  "bare, pale yellow stone, and "+\
  "all the windows have metal bars. The floor and ceiling is the same yellow " +\
  "stone as the walls, and all the doors are heavily reinforced.\n"

#define WALL_ITEM ({"walls", "stone walls", "wall", "stone wall"})
#define WALL_DESC \
  "The stone walls are bare, massive and heavy.\n"

#define STONE_ITEM ({"stone", "yellow stone", "pale yellowstone"})
#define STONE_DESC \
  "The stone is pale yellow, cool and hard.\n"

#define FLOOR_ITEM ({"floor", "floors"})
#define FLOOR_DESC \
  "The floor consists of the same massive yellow stone as the walls.\n"

#define WINDOW_ITEM ({"window", "windows"})
#define WINDOW_DESC \
  "The windows all have massive metal bars, making it impossible to enter "+\
  "(or leave) that way.\n"

#define BAR_ITEM ({"bar", "bars", "metal bar", "metal bars"})
#define BAR_DESC \
  "It is hard to see what kind of metal it really is made from, but it seems "+\
  "hard and strong, and it is thick enough to make it impossible to break even "+\
  "if it was made from a rather soft metal.\n"

#define JAIL_STD_ITEMS \
  add_item(  WALL_ITEM, WRAP(  WALL_DESC)); \
  add_item( STONE_ITEM, WRAP( STONE_DESC)); \
  add_item( FLOOR_ITEM, WRAP( FLOOR_DESC)); \
  add_item(WINDOW_ITEM, WRAP(WINDOW_DESC)); \
  add_item(   BAR_ITEM, WRAP(   BAR_DESC))
  
