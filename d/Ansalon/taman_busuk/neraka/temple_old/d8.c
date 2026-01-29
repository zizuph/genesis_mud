/* Ashlar, 30 Sep 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit TEMPLE_BASE;

object priest, d1, d2;

void
reset_neraka_room()
{
    if (!objectp(d1))
        d1 = clone_npc(NNPC + "templeguard");
    if (!objectp(d2))
        d2 = clone_npc(NNPC + "templeguard");
    if (!objectp(priest))
    {
    	priest = clone_npc(NNPC + "priest");
    	priest->set_patrol_time(20);
    	priest->set_patrol_path(({"s","sw","se","s","s","sw","ne","n","e",
    	    "ne","nw","ne","nw","w"}));
    	priest->start_patrol();
    }
}

string
long_descr()
{
    return "This is a wide hallway in the lower level of the temple. " +
    "West and east of here are the bases of two staircases leading " +
    "up. The hallway itself continues south.\n";
}

void
create_neraka_room()
{
    set_short("wide hallway in the lower level of the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"base","bases","staircase","staircases"}),
    "The staircases are east and west of here.\n");
    add_item("hallway","@@long_descr");

    reset_room();

    add_exit(NTEMPLE + "d7", "west");
    add_exit(NTEMPLE + "d9", "east");
    add_exit(NTEMPLE + "d5", "south");
}


