/*
 * This room contains the common board for all players, mortals as well as
 * immortals.
 *
 * Nick, 921223
 *
 * Added new common board: Mercade, 23 March 1994
 */

#pragma save_binary

#include <stdproperties.h>
#include "default.h"

#define COMMON_BOARD "/d/Genesis/obj/common_master"

void
create_room()
{
    set_short("In the common board room");
    set_long(break_string(
    "You are standing in the room where the common board is. It's common "+
    "for all races in Genesis, immortals as well as mortals. "+
    "There is a small golden plaque on the wall.", 75) + "\n");

    add_item( ({ "golden plaque", "plaque" }), "Why don't you read it.\n");

    add_cmd_item( ({ "golden plaque", "plaque" }), "read",
        break_string("In this room Archwizards can banish people from "+
        "writing silly notes on the common board. Use <banish -l> " +
        "to see all banishments, <banish name> to banish people and " +
        "<unbanish name> or <banish -r name> to forgive people and " +
        "re-allow them to use the board again.", 75) + "\n");

    add_exit(THIS_DIR + "entrance", "east");

    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);

    this_object()->reset_room();
}

void
reset_room()
{
    seteuid(getuid(this_object()));

    /*
     * This may seem like a strange construct, but I want the master object
     * to be in this room and this construct works, so let it be.
     */
    COMMON_BOARD->teleledmingsanka();
    find_object(COMMON_BOARD)->move(this_object(), 1);
}