// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You are walking along the north corridor of the top "+
      "level of the castle. The red carpet beneath you muffles the "+
      "sound of your footsteps as you walk. The air here is hot, since "+
      "many windows line the west wall to let in sunshine. The hallway "+
      "separates into two ways here.\n");
    add_item("carpet","The red carpet is soft and warm.\n");
    add_item("windows","Through the windows, you can see the streets of "+
      "the noble district.\n");

    add_exit(NOBLE + "castle/c45", "south", 0, 0);
    add_exit(NOBLE + "castle/c41", "east", 0, 0);
    add_exit(NOBLE + "castle/c39", "west", 0, 0);
}


