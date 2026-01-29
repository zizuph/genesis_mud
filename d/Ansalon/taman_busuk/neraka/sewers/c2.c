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
    return "This is a dark hallway among the crypts below Neraka. " +
    "The air is dry and dusty, with a faint hint of something " +
    "unpleasant. East and west are smaller crypts, while the " +
    "hallway continues north. A crumbling tapestry hangs on the " +
    "south wall.\n";
}

void
create_neraka_room()
{
    set_short("in a dark hallway");
    set_long("@@long_descr");

    add_crypt_items();
    add_item("hallway","@@long_descr");
    add_item(({"tapestry","crumbling tapestry"}),
    "The tapestry, faded with age and almost crumbling to dust, " +
    "depicts mounted men battling what appears to be ogres.\n");
    add_item("south wall",
    "The south wall contains a crumbling tapestry.\n");
    add_item("crypts","There are crypts to either side of the " +
    "hallway, dark and foreboding.\n");

    remove_prop(ROOM_I_LIGHT);

    add_exit(NSEWER + "c1", "west");
    add_exit(NSEWER + "c3", "east");
    add_exit(NSEWER + "c4", "north");

    reset_room();
}


