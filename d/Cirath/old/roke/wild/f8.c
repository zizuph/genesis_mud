/*
 * f8.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("Forest");
    set_long("You are on a small track on the northern edge of the forest. " +
             "There is lots of high grass streching north towards the " +
             "mountains far away. South you see the thick and dark forest. " +
             "You can also hear sounds from animals.\n");

    add_item("grass", "It's ordinary green grass.\n");

    add_exit("f7", "south");
    add_exit("f9", "east");
}
