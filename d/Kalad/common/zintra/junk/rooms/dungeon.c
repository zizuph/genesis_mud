inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

object doorb;

void
reset_room()
{
    present("key rack")->reset_container();
}    

void
create_room()
{
    set_short("Dungeon");
    set_long(break_string(
"This is the dungeon of the Blackhands.  Here, the more dangerous prisoners " +
"are kept and abused.  To the north is the torture chamber, from which you " +
"can hear strange sounds eminating.  There is a small note tacked on the " +
"wall next to the door.\n", 78));

    add_exit(G_ROOMS + "torture", "north", 0);
    add_exit(G_ROOMS + "basement", "east", "@@block");

    add_item(({"lanterns", "lantern"}), BS(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n"));

    add_item("window", BS("On the door is a tiny window.  You can barely " +
"make out a tiny cell on the other side.\n"));

    add_item("note", "Its tacked to the wall, next to the door.\n");

    INSIDE

    (doorb = clone_object(G_OBJ + "cdoorb"))->move(this_object());
    room_add_object(G_OBJ + "key_rack");
}

int
block()
{
    if (MEMBER(TP)) return 0;
    if (TP->query_wiz_level())
    {
        write(BS("Only guild members are allowed that way, but we'll make " +
            "an exception just this once.\n"));
        return 0;
    }
    write(BS("Only guild members are allowed that way.  You shouldn't even " +
        "be here.  Better leave quick, before the guard shows up.\n"));
    return 1;
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
    if (str != "note") return 0;
    write (BS("The note reads:\nEnemies of the guild are now kept " +
"in this cell.  Please make sure its kept locked.  Any of you bloody " +
"rouges caught picking the lock, will be chained up in the torture chamber." +
"\n\n                                      -The Management.\n"));
    return 1;
}

object
get_door_ob()
{
    return doorb;
}



