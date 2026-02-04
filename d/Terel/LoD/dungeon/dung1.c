/*
 * dung1.c
 *
 * A dungeon below the Legion of Darkness quarters.
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
    
    add_exit(DUNG_DIR + "entrance", "north", 0);
    add_exit(DUNG_DIR + "dung2", "south", 0);
    
    add_door_exit(({"door", "oak door", "western door", "west door",
                    "west-door", "door 1", "first door"}),
                  ({"w", "west"}),
                  "A sturdy oak door. The vertical oak planks have " +
                  "been reinforced by horizontal iron bars. There is " +
                  "an over-sized iron lock in one of the oak planks. " +
                  "The number 1 has been burnt into the door.\n",
                  DUNG_DIR + "cell_1", "_cell_door_1", 0,
                  ({"lock", "iron lock"}), 1, 45 + random(11),
                  get_key_code(1)
                  );
    
    add_door_exit(({"door", "oak door", "eastern door", "east door",
                    "east-door", "door 2", "second door"}),
                  ({"e", "east"}),
                  "A sturdy oak door. The vertical oak planks have " +
                  "been reinforced by horizontal iron bars. There is " +
                  "an over-sized iron lock in one of the oak planks. " +
                  "The number 2 has been burnt into the door.\n",
                  DUNG_DIR + "cell_2", "_cell_door_2", 0,
                  ({"lock", "iron lock"}), 1, 45 + random(11),
                  get_key_code(2)
                  );

    reset_room();
}
