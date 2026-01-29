/*
 * orc_road2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Gresolle 1992 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("forest intersection");
    set_long("This is a small intersection in the middle of a dark forest.\n" +
             "Three paths meet here, one leading west to the populated " +
             "areas of Nyreese, one to the east towards the river, that together " +
             "with the high mountains divides the island, and finally the " +
             "third path that lead north to what looks like a small opening " +
             "between the trees.\n");

    add_exit("orc_road1", "west");
    add_exit("orc_road3", "east");
    add_exit("orc_play", "north");
}
