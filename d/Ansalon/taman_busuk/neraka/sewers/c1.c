/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>

inherit SEWER_BASE;

object s1,s2;

void
reset_neraka_room()
{
    if (!objectp(s1))
        s1 = clone_npc(NNPC + "skeleton");
    if (!objectp(s2))
        s2 = clone_npc(NNPC + "skeleton");
}

string
long_descr()
{
    return "This is a dark crypt somewhere below Neraka. The air is " +
    "dry and dusty, with a faint hint of something unpleasant. A " +
    "stone staircase in a corner of the room leads up into darkness. " +
    "To the east, the room opens up into a larger hallway.\n";
}

void
create_neraka_room()
{
    set_short("in a dark crypt");
    set_long("@@long_descr");

    add_crypt_items();
    add_item("crypt","@@long_descr");
    add_item("hallway",
    "A larger hallway is to the east, mostly lost in darkness.\n");
    add_item(({"staircase","stone staircase"}),
    "The stone staircase sits in a corner of the room. It winds slowly " +
    "upwards, into darkness.\n");

    remove_prop(ROOM_I_LIGHT);

    add_exit(NSEWER + "c2", "east");
    add_exit(NSEWER + "stair1", "up");

    reset_room();
}


