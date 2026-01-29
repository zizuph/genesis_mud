/*
 * red_r1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("small road between some houses");
    set_long("You're standing in the middle of a small road leading past " +
             "some houses in the red light district of Cadu. To the " +
             "northeast you spot a brewery delivering beer and other " +
             "alcoholic beverages to the pub west of here, and south " +
             "of you is the entrance to the local 'escort service'.\n");

    add_exit("red_r2", "east");
    add_exit("red_pub", "west");
    add_exit("red_bordell", "south");
}
