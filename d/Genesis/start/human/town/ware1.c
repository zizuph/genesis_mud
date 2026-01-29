#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("A large warehouse");
    set_long("\n"+
             "This is a very large warehouse.\n"+
             "Many large crates are piled up in here. Some of them\n"+
             "have strange labels and come from quite unknown places.\n"+
             "");

    add_item(({"crates" }),"You see nothing special about the crates except for the labels.\n"+
    "");
    add_item(({"labels" }),"They seem to be from far away places.\n"+
    "");
    add_item(({"room" }),"It is very spacious.\n"+
    "");

    add_exit(TOWN_DIR + "pier6","north");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");
}
