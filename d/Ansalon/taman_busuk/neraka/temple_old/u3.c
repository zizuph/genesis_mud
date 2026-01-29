/* Ashlar, 21 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit TEMPLE_BASE;

object priest,guard1,guard2;

void
reset_neraka_room()
{
    if (!objectp(priest))
        priest = clone_npc(NNPC + "priest");
    if (!objectp(guard1))
        guard1 = clone_npc(NNPC + "templeguard");
    if (!objectp(guard2))
        guard2 = clone_npc(NNPC + "templeguard");
}

string
long_descr()
{
    return "This is a wide hallway in the upper level of the temple. " +
    "The hallway leads east and west, and a doorway leads north out " +
    "to a balcony. To the south, a staircase leads upwards. " +
    "A thick blood-red carpet runs the length of the " +
    "hallway.\n";
}

void
create_neraka_room()
{
    set_short("wide hallway in the upper level of the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item("hallway","@@long_descr");
    add_item(({"carpet","thick carpet","blood-red carpet",
    	"thick blood-red carpet"}),
    	"The carpet stretches the full length of the hallway. It is thick " +
    	"and comfortable to walk on.\n");
    add_item("doorway","The doorway to the north leads out to a balcony.\n");
    add_item("staircase","The staircase leads upwards into darkness.\n");

    reset_room();

    add_exit(NTEMPLE + "u4", "east");
    add_exit(NTEMPLE + "u2", "west");
    add_exit(NTEMPLE + "balcony", "north");
    add_exit(NTEMPLE + "u6", "south");
    add_exit(NTEMPLE + "u6", "up", 0, 1, 1);
}


