inherit "/d/Gondor/common/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void    reset_room();

object  guard;

void
create_room()
{
    set_long(BSN("A bedroom inside the outer walls of Minas Tirith. "
      + "This is where the guards rest on the longer night-shifts. "
      + "A doorway is leading south into the guard room. Along the walls "
    + "are sleeping bunks and some blankets."));
    set_short("In a restroom at the Great Gate of Minas Tirith");

    add_item(({"door", "doorway", }),
        "The doorway is leading south into the guard room.\n");
    add_item(({"desk"}), BSN(
        "A small desk, probably for the paperwork that has to be done "
      + "here at the gate."));
    add_item(({"bunks", "bed", "bunk", }), BSN(
        "A simple wooden frame filled with a straw mattress and covered by a "
      + "few woollen blankets. Not comfortable, but sufficient to get some "
      + "rest while on duty."));
    add_exit(MINAS_DIR + "wall/ninwall1", "south", 0, 1);
    add_prop(ROOM_I_INSIDE,1);

    reset_room();
}

void
reset_room()
{
    if (objectp(guard))
        return;

    guard = clone_object(MINAS_DIR + "npc/wall_guard");
    guard->arm_me();
    guard->move(TO);
}
