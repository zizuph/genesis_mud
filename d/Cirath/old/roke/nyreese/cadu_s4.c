/*
 * cadu_s4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("The shore of Cadu");
    set_long("You are at the west end of the shore south of Cadu.\n" +
	     "Here the mountains begin to tower up in the sky. " +
	     "The shore continues to the west as far as you can see. " +
	     "There is probably nothing of interest here, if you're not " +
	     "interested in the soft sand beneath your feet. Back east " +
	     "you can see some fishermen and a few small houses.\n");

    BEACH;

    add_exit("cadu_s6", "west");
    add_exit("cadu_s3", "east");
    add_item("sand", "It is white, slightly damp and very soft.\n");
}  
