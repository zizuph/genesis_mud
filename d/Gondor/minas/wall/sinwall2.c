inherit "/d/Gondor/common/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void    reset_room();

object  galdor;

void
create_room()
{
    set_long(BSN("An office inside the outer walls of Minas Tirith. "
      + "This is where the Captain of the Guard spends his time when on duty. "
      + "A doorway is leading north into the guard room. In the corner stands "
      + "a small desk, and in a corner is a cot."));
    set_short("In an office at the Great Gate of Minas Tirith");

    add_item(({"door", "doorway", }),
        "The doorway is leading north into the guard room.\n");
    add_item(({"desk"}), BSN(
        "A small desk, probably for the paperwork that has to be done "
      + "here at the gate."));
    add_item(({"cot", "bed", }), BSN(
        "A simple wooden frame filled with a straw mattress and covered by a "
      + "few woollen blankets. Not comfortable, but sufficient to get some "
      + "rest while on duty."));
    add_exit(MINAS_DIR + "wall/sinwall1", "north", 0, 1);
    add_prop(ROOM_I_INSIDE,1);

    reset_room();
}

void
reset_room()
{
    if (objectp(galdor))
        return;

    galdor = clone_object(MINAS_DIR + "npc/galdor");
    galdor->move(TO);
}
