/*
 *   /d/Gondor/ithilien/poros/manor/kitchen.c
 *
 *   A room inside the manor that serves as a hidden base for corsairs.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

static object  cook;

public void
reset_room()
{
    if (!objectp(cook))
    {
      cook = clone_object(POROS_DIR + "npcs/cook");
      cook->arm_me();
      cook->move_living("down", TO);
      }
}

void
create_manor()
{
    set_area("kitchen");
    set_extraline("A large fireplace rests in the southeastern corner of "
      + "the room, within which a very large iron kettle sits. Other pots, "
      + "pans, and various utensils hang from the walls, and a table stands "
      + "near the center of the room. A doorway out is to the west.");

    add_exit(POROS_DIR + "manor/dininghall", "west", 0, 1);

    add_item(({"kitchen", "floor", "ground"}), BSN(
        "The kitchen shows signs of recent use. Provisions as well as cooking "
      + "utensils are stored in this room. You can smell that a meal was "
      + "prepared in this room not too long ago."));

    add_item(({"fireplace", "large fireplace"}), BSN(
        "This fireplace is where most of the meals in the manor are prepared. "
      + "Currently an iron kettle sits in the fireplace, but you also notice "
      + "there is a rack that can be used for roasting as well. Warm embers "
      + "can be seen amongst the ashes where a recent fire was."));

    add_item(({"kettle", "iron kettle"}), BSN(
        "This is a large iron kettle that is used for cooking stew and "
      + "other gruel. You notice it is empty now, save for traces of the "
      + "last meal along its sides and bottom."));

    add_item(({"pots", "pans", "utensils"}), BSN(
        "They hang along the kitchen walls, and some are lying on the "
      + "table. They are plain, and of little value."));

    add_item(({"table"}), BSN(
        "The table is used primarily for food preperation. You can see "
      + "some scrapes of food, as well as some cooking utensils lying "
      + "on top of it."));

    add_item(({"provisions"}), BSN(
        "Some provisions are also stored here in the kitchen. The supplys "
      + "are used in making meals for the corsairs based here in "
      + "the manor."));

    reset_room();

}
