/*
 * cadu_q9.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object agatha;

void
reset_room()
{
    if (!present("hut", TO))
        clone_object(ROKEDIR + "obj/mm_hut")->move(TO);
    
    /*(REDLIGHT+"mm_inside")->teleledningsanka();*/

/*
    if (!objectp(agatha))
	(agatha = clone_object(ROKEDIR + "npc/oldbitch"))->move(TO);
*/
}

void
create_room()
{
    set_short("Town square");
    set_long("You are at the northeast corner of the town square.\n" +
             "When you look to the east you spot the bank and " +
             "the shop. In the south and west is the large centre " +
             "of Cadu.\n");

    add_exit("cadu_q5", "southwest");
    add_exit("cadu_q8", "west");
    add_exit("cadu_q6", "south");
    add_exit("cadu_a1", "east");

    /*
       clone_object(REDLIGHT+"mm_box")->move(TO);
    */
    reset_room();
}
