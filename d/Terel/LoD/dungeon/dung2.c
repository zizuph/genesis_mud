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
    
    set_long(query_long() + "There appears to be two cells here, one " +
             "in the eastern wall and the other in the western wall.\n");
    
    add_item(({"cell", "cells"}), "There are two cells here. One is seen " +
             "to the west and the other is found to the east.\n");
    
    add_exit(DUNG_DIR + "dung1", "north", 0);
    add_exit(DUNG_DIR + "dung3", "south", 0);
    
    add_door_exit(({"door", "oak door", "western door", "west door",
                    "west-door", "door 3", "third door"}),
                  ({"w", "west"}),
                  "A sturdy oak door. The vertical oak planks have " +
                  "been reinforced by horizontal iron bars. There is " +
                  "an over-sized iron lock in one of the oak planks. " +
                  "The number 3 has been burnt into the door.\n",
                  DUNG_DIR + "cell_3", "_cell_door_3", 0,
                  ({"lock", "iron lock"}), 1, 45 + random(11),
                  get_key_code(3)
                  );
    
    add_door_exit(({"door", "oak door", "eastern door", "east door",
                    "east-door", "door 4", "fourth door"}),
                  ({"e", "east"}),
                  "A sturdy oak door. The vertical oak planks have " +
                  "been reinforced by horizontal iron bars. There is " +
                  "an over-sized iron lock in one of the oak planks. " +
                  "The number 4 has been burnt into the door.\n",
                  DUNG_DIR + "cell_4", "_cell_door_4", 0,
                  ({"lock", "iron lock"}), 1, 20 + random(5),
                  get_key_code(4)
                  );

    reset_room();
}
