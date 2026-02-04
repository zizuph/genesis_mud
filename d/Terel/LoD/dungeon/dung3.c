/*
 * dung1.c
 *
 * A generic dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "dungeon/dungeon_room";

#define DUNG_DIR   (LOD_DIR + "dungeon/")

public void
create_room()
{
    ::create_room();
    
    set_long(query_long() + "There appears to be three cells here, one " +
             "in the eastern wall, one in the western wall, and a " +
             "third in the southern wall.\n");
    
    add_item(({"cell", "cells"}), "There are two cells here. One is seen " +
             "to the west and the other is found to the east.\n");
    
    add_exit(DUNG_DIR + "dung2", "north", 0);
    
    add_door_exit(({"door ", "oak door", "western door", "west door",
                    "west-door", "door 5", "fifth door"}),
                  ({"w", "west"}),
                  "A sturdy oak door. The vertical oak planks have " +
                  "been reinforced by horizontal iron bars. There is " +
                  "an over-sized iron lock in one of the oak planks. " +
                  "The number 5 has been burnt into the door.\n",
                  DUNG_DIR + "cell_5", "_cell_door_5", 0,
                  ({"lock", "iron lock"}), 1, 80+random(11),
                  get_key_code("cell_5")
                  );
    
    add_door_exit(({"door", "oak door", "eastern door", "east door",
                    "east-door", "door 6", "sixth door"}),
                  ({"e", "east"}),
                  "A sturdy oak door. The vertical oak planks have " +
                  "been reinforced by horizontal iron bars. There is " +
                  "an over-sized iron lock in one of the oak planks. " +
                  "The number 6 has been burnt into the door.\n",
                  DUNG_DIR + "cell_6", "_cell_door_6", 0,
                  ({"lock", "iron lock"}), 1, 45 + random(11),
                  get_key_code(6)
                  );
    
    add_door_exit(({"door", "oak door", "southern door", "south door",
                    "south-door", "door 7", "seventh door"}),
                  ({"s", "south"}),
                  "A sturdy oak door. The vertical oak planks have " +
                  "been reinforced by horizontal iron bars. There is " +
                  "an over-sized iron lock in one of the oak planks. " +
                  "The number 7 has been burnt into the door.\n",
                  DUNG_DIR + "cell_7", "_cell_door_7", 0,
                  ({"lock", "iron lock"}), 1, 45 + random(11),
                  get_key_code(7)
                  );

    reset_room();
}
