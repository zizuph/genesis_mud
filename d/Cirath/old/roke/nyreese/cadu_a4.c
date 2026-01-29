/*
 * cadu_a4.c
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
    set_short("Outside pigeons");
    set_long("You are in one of Cadu's small alleys.\n" +
	     "In the east are lots of people walking towards " +
	     "the town square, and in the west you can spot a small " +
	     "group of badly dressed, dirty and tired people. " +
	     "A burned-down building is to the north.\n");
 
    add_exit("cadu_pig", "north");
    add_exit("cadu_a5" , "west");
    add_exit("cadu_a3" , "east");
}
