inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short("Master's room");
    set_long(BS(
"The office of the Master Blackhand, this room is cleaner than many in " +
"this area, but almost completely unfurnished.  This room is lit with the " +
"same standard lanterns you see all around this area.  Behind a small oak " +
"desk is a very old man.\n"));

    add_exit(G_ROOMS + "guard_room", "east", 0);

    add_item(({"lanterns", "lantern"}), BS(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n"));

    add_item("plaque", BS("It is so polished that it gleams.  The owner " +
"obviously treasures it a great deal.  You can make out some words written " +
"on the surface of the plaque.\n"));

    add_item(({"desk", "small desk", "oak desk", "small oak desk"}), BS(
"The desk is very neatly organized.  In fact, there " +
"is only one object on its surface -- a brass plaque.\n"));

    INSIDE
    add_prop(ROOM_M_NO_ATTACK, "You begin to attack the master, but " +
       "something holds you back.  Perhaps its the evil gleam in his eyes.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "You begin to attack the master, but " +
       "something holds you back.  Perhaps its the evil gleam in his eyes.\n");
    room_add_object(G_MON + "master");
}

void
init()
{
    ::init();
    add_action("read", "read");
}

int
read(string str)
{
    NF("Read what?\n");
    if (!str) return 0;
    if (str != "plaque") return 0;
    write ("The plaque reads, 'There is no honor among theives.'  " +
        "Words to live by.\n");
    return 1;
}
