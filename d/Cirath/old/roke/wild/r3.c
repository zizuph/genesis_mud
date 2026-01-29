/*
 * r3.c
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
    set_short("the end of the road");
    set_long("This is the base of a huge mountain that effectively stops all " +
             "travellers who don't walk or ride on a horse. Fortunately the " +
             "mountain isn't very steep so it is possible to walk both south " +
             "and east between some rocks.\n");

    add_item("rocks", "The rocks are very large and look rather" +
             "strange.\n");

    add_exit("p1", "south");
    add_exit("p3", "east");
    add_exit("r2", "west");
}
