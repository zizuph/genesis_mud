// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You stand in the mid-section of the northwest tower "+
      "in the castle of the High-Lord. Hot wind, and bright sunlight "+
      "steams from the windows in the wall next to you. Two ways, "+
      "one east, one south, lead out of this tower area into halls. "+
      "The stairwell continous up further, or back down. "+
      "You see nothing special here, save for the carpet below.\n");
    add_item("carpet","The red carpet is soft and warm.\n");
    add_item("windows","Through the windows, you can see the streets of "+
      "the noble district.\n");

    add_exit(NOBLE + "castle/c39", "east", 0, 0);
    add_exit(NOBLE + "castle/c43", "south", 0, 0);
    add_exit(NOBLE + "castle/ctower1", "up", 0);
    add_exit(NOBLE + "castle/c4", "down", 0);
}


