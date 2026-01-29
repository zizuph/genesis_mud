/*
 * monk_tree.c
 * FIXA
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("Up in a high tree");
    set_long("You are high up among the branches of a huge tree. Perhaps " +
             "you should flap your wings and fly home instead of trying " +
             "to pass the dragon. He doesn't like the undead.\n");

    add_exit("p6", "down");
}
