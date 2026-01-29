/*
 * monk_store.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*Kaheda guild store added by Mona July ‘96
*for the sale of herbpouches*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>

void
create_room()
{
    set_short("Kaheda store.");
    set_long("The bare oak floor of this room has " +
             "been freshly swept, and there is a " +
             "new wooden plaque hanging overhead.\n");
    add_exit("monk_discuss", "north");
    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("plaque",
             " --------------\n" +
             "| Herbpouches: |\n" +
             "|  12 Silver   |\n" +
             "|    Coins.    |\n" +
             " --------------\n");
    add_cmd_item("plaque", "read",
                 " --------------\n" +
                 "| Herbpouches: |\n" +
                 "|  12 Silver   |\n" +
                 "|    Coins.    |\n" +
                 " --------------\n");

}
