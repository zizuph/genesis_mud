/*
 * monk_h1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include "defs.h"

void
create_room()
{
    set_short("a large hall");

    set_long("You are in a large hall on the second floor. The walls are " +
             "covered by great paintings with scenes from different wars " +
             "in the history of Nyreese. To your south you can see a " +
             "courtroom, to the west there is a small dining room. The " +
             "exit to the north are guarded by two sturdy monks.\n");

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item(({"monk", "monks"}), "The monks are big and hairy.\n");
    add_item(({"painting", "paintings"}),
             "You can see five paintings here.\n" +
             "You realize that it must be the five councilmembers.\n");

    INSIDE;
    add_exit("monk_entr", "down");
    add_exit("monk_h2", "north");
    add_exit("monk_council", "south");
    add_exit("monk_dinner", "west");
    add_exit("monk_discuss", "east");
}
