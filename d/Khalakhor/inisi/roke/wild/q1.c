/*
 * q1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("narrow path");
    set_long("You are on a narrow path leading from the abandoned monastery " +
             "towards a mountain top. North of you is the monastery building " +
             "and to the south you see the blue ocean.\n");

    add_item(({"building", "monastery"}),
             "It is an old abandoned monastery.\n");
    add_item("ocean", "It is rather far away.\n");
    add_item("mountain", "The mountain top is to the northeast.\n");
    
    add_exit("q2", "east", -1, 3);
    add_exit("p6", "west");
}
