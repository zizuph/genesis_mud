/*
 * cadu_b2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

object sparkleboat;

/*
void
start_ship() //FIXA 
{
    if (!sparkleboat) 
    {
	sparkleboat = clone_object(SHIPS + "gontsparkle/ship");
	sparkleboat->move(TO);
    }

    sparkleboat->start_ship(0);
}
*/

void
create_room()
{
    set_short("Pier");
    set_long("You are on the pier south of Cadu.\n" +
             "This is where the boat to Sparkle lands. " +
             "To the north the pier continues towards land " +
             "and to the west there seems to be some kind " +
             "of tower on the pier. To the east the pier abruptly " +
             "drops off, and and the sea crashes up against it.\n");

    add_exit("cadu_b4", "north");
    add_exit("cadu_b3","west");

    add_item("tower", "The tower is too far west to be properly examined.\n");

/*

    set_alarm(1.0, 0.0, start_ship);

    add_prop(OBJ_S_WIZINFO,
      "type 'Call here start_ship' to restart the boat.\n"); 
*/
    BEACH;
}
