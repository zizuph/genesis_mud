/*
 * /d/Gondor/clubs/storytellers/rooms/board_room.c
 */
inherit "/d/Gondor/std/room";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include "../defs.h"

string read_sign();

void
create_gondor()
{
    set_short("a quiet room off the hallway");
    set_long("This quiet room is well-lit, with a doorway leading south. "+
        "On the opposite wall is a large bulletin board, next to which "+
        "is a sign.\n");
    add_item("south doorway", "It is arched with smooth white stones. " +
        "Beyond it is the hallway from which you enterred this room.\n");
    add_item("sign", &read_sign());
    add_cmd_item("sign", "read", &read_sign());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(STORYT_DIR + "rooms/ehallway", "south", 0, 0);
    clone_object(STORYT_DIR + "obj/board")->move(TO);
}

public nomask string
read_sign()
{
    return "The Storytellers board.\n";
}

