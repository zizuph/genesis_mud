/* Loaded by cave1.c */

inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"

void
create_clone_handler()
{
    set_default_area(THIEF_LAIR_DIR);

    // NPCs:

    add_clone(THIEF_LAIR_DIR + "npc/standard_thug",  1,
	      2 + random(2), THIEF_LAIR_DIR + "cave7");
    add_clone(THIEF_LAIR_DIR + "npc/standard_thug",  2, 
	      4 + random(4), THIEF_LAIR_DIR + "cave9");  
    add_clone(THIEF_LAIR_DIR + "npc/lieutenant", 3, 1,
	      THIEF_LAIR_DIR + "cave7");   
    /*
      add_clone(THIEF_LAIR_DIR + "npc/standard_thief",  4, 2 + random(2),
    THIEF_LAIR_DIR + "cave7");     
    add_clone(THIEF_LAIR_DIR + "npc/standard_thief", 6, 4 + random(4), 
    THIEF_LAIR_DIR + "cave9");
    add_clone(THIEF_LAIR_DIR + "npc/standard_thief", 7, random(3),
    THIEF_LAIR_DIR + "cave9");
    */

    add_clone(THIEF_LAIR_DIR + "npc/tevalanar",  5, 1, 
	      THIEF_LAIR_DIR + "cave9");
    add_clone(THIEF_LAIR_DIR + "npc/shopkeeper",  8, 1, 
	      THIEF_LAIR_DIR + "cave9"); 

    // Non-livings:

    add_clone(THIEF_LAIR_DIR + "obj/hard_bread", 9, 2 + random(6),
	      THIEF_LAIR_DIR + "cave10");
    add_clone(THIEF_LAIR_DIR + "obj/fruits_and_nuts", 10, 20 + random(20),
	      THIEF_LAIR_DIR + "cave10");
}
