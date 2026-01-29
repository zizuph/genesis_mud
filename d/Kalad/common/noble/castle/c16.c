// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a kitchen of the Castle of the High-Lord");
    INSIDE;
    set_long("You now find yourself in a smoke-filled room. "+
      "The ground here is bare, and you see many stains and "+
      "food debris. The kitchen is massive, and stretches all "+
      "the way to the east. Along the walls, you see many "+
      "cooking fires with iron pots over them. Tables dot the "+
      "room with platters of food, and servants come " +
      "to take them.\n");
    add_item("fires","The burn the iron pots filled with water "+
      "to a boiling temperature.\n");
    add_item("pots","Large iron pots of water and food.\n");
    add_item("tables","The tables are covered with food of all "+
      "sorts, cooked and uncooked.\n");

    add_exit(NOBLE + "castle/c12", "north", 0, 0);
    add_exit(NOBLE + "castle/c21", "south", 0, 0);
    add_exit(NOBLE + "castle/c17", "east", 0, 0);
    add_exit(NOBLE + "castle/c15", "west", 0, 0);
}


