/*
 * monk_robes.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("robe store");

    set_long("You are in the robe store of the Kaheda Order.\n" +
             "This room is extremely featureless and you wonder if the creator\n" +
             "lost all ideas when he made this room. Probably he didn't lose \n" +
             "them all because there are some really nice features here after\n" +
             "all. Here you can buy the special made monk robes. Please note that\n"
             + "the robes are so special that you can't sell them.\n" +
             "There is a small sign here.\n");

    add_item("sign",
             "To buy yourself a robe, suitable for your rank, type 'buy robe'.\n" +
             "To see what it costs, type 'price'\n");
    add_cmd_item("sign", "read",
                 "To buy yourself a robe, suitable for your rank, type 'buy robe'.\n" +
                 "To see what it costs, type 'price'\n");

    INSIDE;

    add_exit("monk_discuss", "north");
}
