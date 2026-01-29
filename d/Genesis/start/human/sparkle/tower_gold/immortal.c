#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <std.h>

#include "../defs.h"

void
create_room() 
{
    object ob;

    set_short("In the immortal discussion room");

    set_long("\n"+
             "You are standing in the immortal discussion room. There is\n" +
             "a board here that you can use as a forum for discussions.\n\n");

    add_exit(TOWN_DIR + "tower", "east");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "This is a room for writing, not fighting.\n");
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    room_add_object(TOWN_DIR + "imm_board");
}
