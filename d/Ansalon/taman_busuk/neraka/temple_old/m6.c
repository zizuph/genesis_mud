/* Ashlar, 21 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit TEMPLE_BASE;

object guard;

void
reset_neraka_room()
{
    if (!objectp(guard))
        guard = clone_npc(NNPC + "templeguard");
}

string
long_descr()
{
    return "This is a wide hallway on the main level of the temple. " +
    "The hallway leads north of here, while to the south a pair of " +
    "doors block the hallway.\n";
}

void
create_neraka_room()
{
    set_short("wide hallway in the main level of the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item("hallway","@@long_descr");
    add_item(({"pair of doors","doors","door"}),
    "The large iron-bound doors are closed, shutting off the south exit.\n");
    add_cmd_item(({"pair of doors","doors","open"}),
    "open",
    "You cannot open the doors; they seem barred on the inside.\n");

    reset_room();

    add_exit(NTEMPLE + "m1", "north");
}


