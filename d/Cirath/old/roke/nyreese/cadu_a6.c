/*
 * cadu_a6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("Narrow road");
    set_long("You are in one of Cadu's small alleys.\n" +
	     "To your south is the big town square. In the north you " +
	     "can see something shiny over the treetops.\n");
    
    add_exit("cadu_a7", "north");
    add_exit("cadu_a2", "south");
}
