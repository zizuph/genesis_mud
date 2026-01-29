/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit SEWER_BASE;

object s1;

void
reset_neraka_room()
{
    if (!objectp(s1))
        s1 = clone_npc(NNPC + "skeleton");
}

string
long_descr()
{
    return "This is a dark crypt somewhere below Neraka. The air is " +
    "dry and dusty, with a faint hint of something unpleasant. There " +
    "is a stone bier against the south wall. To the west, the room " +
    "opens up into a larger hallway.\n";
}

void
create_neraka_room()
{
    set_short("in a dark crypt");
    set_long("@@long_descr");

    add_crypt_items();
    add_item("crypt","@@long_descr");
    add_item("hallway",
    "A larger hallway is to the west, mostly lost in darkness.\n");
    
    add_item(({"bier","stone bier"}),
    "The bier is a large slab of stone standing against the south wall.\n");
    add_item("south wall",
    "There is an opening in the south wall, just above the bier.\n");
    add_item("opening",
    "The opening leads to some sort of tunnel running south and upwards.\n");
    add_cmd_item(({"opening","tunnel","through opening","through tunnel",
    "into opening","into tunnel"}),
    ({"enter","climb","crawl"}),
    ({"@@enter_opening","@@enter_opening","@@enter_opening"}));

    remove_prop(ROOM_I_LIGHT);

    add_exit(NSEWER + "c6", "west");

    reset_room();
}

string
enter_opening()
{
    object other_room;
    object pl;

    LOAD_ERR(NSEWER + "s5");
    other_room = find_object(NSEWER + "s5");

    if (!objectp(other_room))
    {
        write("\nError: Can not load file <" + NSEWER + "s5> Please " +
        "leave a bugreport.\n\n");
        return "";
    }
    pl = TP;

    write("You climb up on the stone bier and crawl through the " +
    "tunnel.\n");
    set_dircmd("opening");
    pl->move_living("M",other_room);
    tell_room(TO,QCTNAME(pl) + " climbs up on the stone bier and " +
    "enters an opening in the wall.\n", pl);
    tell_room(other_room, QCTNAME(pl) + " arrives out of an opening in " +
    "the north wall.\n", pl);
    return "";
}
