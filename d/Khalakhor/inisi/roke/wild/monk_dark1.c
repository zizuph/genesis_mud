/*
 * monk_dark1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

void
create_room()
{
    set_short("dark room");
    set_long("This is a dark room.\n");

/*
    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
*/
    add_prop(ROOM_I_LIGHT, -90);

    INSIDE;

    add_exit("monk_h2", "east");
    //    add_exit("monk_dark2", "west", "@@block");
}

int
block()
{

/*Kollar om det aer ljust i rummet. Daa kan man gaa in*/
/*Till dark2.c                                     */
/*Disabled until we decide what to do . */
/*    if (query_prop(OBJ_I_LIGHT) > 0)*/
/*      return 0; */

    TP->catch_msg("You don't dare to go that way.\n");
    return 1;
}
