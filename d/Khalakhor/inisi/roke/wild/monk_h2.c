/*
 * monk_h2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include "defs.h"

void
create_room()
{
    set_short("a large hall");

    set_long("This hall is quite dirty, but entirely empty with open " +
             "doorways in four directions: north, south, east and west.  " +
             "The west room appears very dark; the south and east rooms " +
             "look dusty but more inviting.  You get a strange feeling from " +
             "the north.\n");
/*
    set_long("You have entered the inner part of the Kaheda guild. Only " +
             "Priests and Priestesses are allowed to enter. To the north " +
             "you can find the secret sanctum of the Kaheda order. To the " +
             "west you can see a dark room and to the east you can hear " +
             "some loud noices from training members of the guild.\n" +
             "There is also a small sign on the western wall.\n");

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("sign",
             "Blindfighting lessons offered, just enter the room to the west.\n");
    add_cmd_item("sign", "read",
                 "Blindfighting lessons offered, just enter the room to the west\n");
*/
    INSIDE;

    add_exit("monk_h1", "south");
    add_exit("monk_dark1", "west");
    add_exit("monk_occtrain1", "east");
    add_exit("monk_sanctum", "north");
}
