/*
 * f4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("In a forest");
    set_long("You are standing in a part of the forest where the trees " +
             "are a little thinner than usual. This would obviously be " +
             "a good spot to do some camping, and judging from the pile " +
             "of coal on the ground someone has done that recently. A " +
             "small path leads east and west from here.\n");

    add_item("coal", "It's an ordinary pile of coal.\n");

    add_exit("fg", "east");
    add_exit("f3", "west");
}
