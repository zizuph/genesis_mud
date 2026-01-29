/*
 * cadu_s2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
reset_room()
{
    if(!present("fisherman", TO))
    {
	clone_object(ROKEDIR + "npc/fisherman")->move(TO);
	tell_room(TO, "A bad smelling fisherman arrives in a boat.\n");
    }
}

void
create_room()
{
    BEACH;
   
    set_short("Docks");
    set_long("These are the docks of Cadu. Fishermen are mending " +
	"torn nets outside a row of small houses to your north. " +
	"To your south are a few small boats, floating in the sea. " +
        "There is an open door in one of the houses.\n");
   
    add_item("boats", "They are very old and dirty.\n");
    add_item(({"net", "nets"}), "The fishermen have indeed a long " +
        "night ahead...\n");
   
    add_exit("cadu_s1", "east");
    add_exit("cadu_s3", "west");
    add_exit("cadu_h2", "north");
   
    reset_room();
}
