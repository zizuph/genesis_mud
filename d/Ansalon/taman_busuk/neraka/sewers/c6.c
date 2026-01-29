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
        s1 = clone_npc(NNPC + "zombie");
    if (!objectp(s2))
        s2 = clone_npc(NNPC + "zombie");
}

string
long_descr()
{
    return "This is a dark hallway among the crypts below Neraka. " +
    "The air is dry and dusty, with a faint hint of something " +
    "unpleasant. East and west are smaller crypts, while the " +
    "hallway continues south. There is a pair of large stone doors " +
    "set in the north wall.\n";
}

void
create_neraka_room()
{
    set_short("in a dark hallway");
    set_long("@@long_descr");

    add_crypt_items();
    add_item("hallway","@@long_descr");
    add_item("north wall",
    "There is a pair of large stone doors set in the north wall, taking " +
    "up most of the it.\n");
    add_item(({"door","doors","stone doors","large stone doors",
    "pair of doors"}),
    "The large stone doors are closed, and there is no obvious way of " +
    "opening them.\n");
    add_item("crypts","There are crypts to either side of the " +
    "hallway, dark and foreboding.\n");

    add_cmd_item(({"door","doors","stone doors","large stone doors",
    "pair of doors"}),
    ({"open"}),
    ({"There is no obvious way of opening these doors from here.\n"}));

    remove_prop(ROOM_I_LIGHT);

    add_exit(NSEWER + "c5", "west");
    add_exit(NSEWER + "c7", "east");
    add_exit(NSEWER + "c4", "south");

    reset_room();
}


