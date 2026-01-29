/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

int hornFound = 0;

void
create_room()
{
    ::create_room();
    set_short("Bloody ritual room of a morbid temple");
    set_long(
      "You stand in a foul-smelling room. The walls are covered with blood. " +
      "The ground is covered with a black rug, on which lay rotting, human " +
      "body parts.\n");
    add_item(({"rug"}),
      "It is covered in blood from the leaking body parts on it.\n");
    add_item(({"body parts", "parts"}),
      "Arms, hands, fingers, legs, a head or maybe two, in different phases " +
      "of decomposion.\n");
    add_item("blood",
      "Much of it is dried and blackened, but some near the body parts is " +
      "fresh and oozing.\n");
    add_prop(OBJ_I_SEARCH_TIME, 10);
    add_prop(OBJ_S_SEARCH_FUN, "search_horn");
    add_item(({"torches"}), "They give light to the room.\n");
    add_exit(TEMPLE_DIR + "temple17", "north", 0);
}

void
reset_room()
{
    hornFound = 0;
}

string
search_horn()
{
    object horn;
    if (hornFound)
        return 0;
    horn = clone_object(QUEST_HORN_FILE);
    horn->move(TP);
    say(QCTNAME(TP) + " found something.\n");
    hornFound = 1;
    return "You find a " + horn->short() + "!\n";
}
