// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

object ob;

void reset_room();

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You stand in the mid-section of the southeast tower "+
      "in the castle of the High-Lord. Hot wind, and bright sunlight "+
      "steams from the windows in the wall next to you. Two ways, "+
      "one west, one north, lead out of this tower area into halls. "+
      "The stairwell continous up further, or back down. "+
      "You see nothing special here, save for the carpet below.\n");

    add_item("carpet","The red carpet is soft and warm.\n");
    add_item("windows","Through the windows, you can see the streets of "+
      "the noble district.\n");

    add_exit(NOBLE + "castle/c71", "west", 0, 0);
    add_exit(NOBLE + "castle/c67", "north", 0, 0);
    add_exit(NOBLE + "castle/ctower6", "up", 0);
    add_exit(NOBLE + "castle/c37", "down", 0);

    reset_room();
}

void
reset_room()
{
    ob = clone_npcs(ob, NOBLE + "npc/castle_guard");
}

