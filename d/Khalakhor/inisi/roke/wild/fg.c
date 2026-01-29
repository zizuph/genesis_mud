/*
 * fg.c
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
    set_short("Just below a cliff");
    set_long("This spot is located just below a cliff, rising high up to " +
             "the north of you, preventing all movement in that direction. " +
             "It is unusually cold here.\n");

    add_item("cliff", "It is an ordinary, unclimbable, stone cliff.\n");

    add_cmd_item("cliff", "climb", "It's still unclimbable!\n");

    add_exit("f4", "west");
    add_exit("fh", "east");
}
