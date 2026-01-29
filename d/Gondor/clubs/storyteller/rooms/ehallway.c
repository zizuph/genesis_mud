/*
 * /d/Gondor/clubs/storytellers/rooms/ehallway.c
 */
inherit "/d/Gondor/std/room";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include "../defs.h"

string read_sign();

void
create_gondor()
{
    set_short("a small hallway in the private section of the house");
    set_long("The small hallway leads ends to the east in a " +
        "doorway. Another doorway in the north wall opens into a " +
        "well-lit room. At the west end of the hallway is a wooden door.\n");
    add_item("north doorway", "It is arched with smooth white stones. " +
        "Beyond it is a room with a bulletin board on the far wall.\n");
    add_item("sign", &read_sign());
    add_cmd_item("sign", "read", &read_sign());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(STORYT_DIR + "rooms/archives", "east", 0, 0);
    add_exit(STORYT_DIR + "rooms/board_room", "north", 0, 0);
    add_exit(STORYT_DIR + "rooms/start_room", "south", 0, 0);
    clone_object(STORYT_DIR + "obj/2f_door_in")->move(TO);
}

public nomask string
read_sign()
{
    write(read_file(STORYT_DIR + "misc/sign3.txt"));
    return "";
}

