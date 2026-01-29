inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Hall");
    set_long(BS("\nYou are in the hall of a large house.  The floor is "
       +"is covered with mats.  A large portrait hangs on the wall.  "
       +"The hall continues to the north.\n\n"));

    add_exit(FARM(ghouse/hall2), "north", 0, 0, 0);
    add_exit(FARM(ghouse/lounge), "west", 0, 0, 0);
    add_exit(FARM(ghouse/cloak), "east", 0, 0, 0);

    add_item(({"mat", "mats"}), BS("The mats are woven from coarse fibres. "
       +"They are old but not too smelly.  They could still do with "
       +"changing though!\n"));

    add_item("portrait", BS("\nA large portrait of an elderly man with a "
       +"flowing white beard.  Despite looking old, something in the eyes "
       +"tells you that this man still has some great power.  There is a "
       +"caption beneath the portrait.\n\n"));

    add_item("caption", BS("\nThe caption is faded by the passing of the "
       +"years.  However, you can just make out 'M.r..n'.\n\n"));

    add_prop(ROOM_I_INSIDE, 1);
}

