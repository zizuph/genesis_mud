/*
 * d1.c
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

    set_short("disgusting chamber");
    set_long("This is a not so pleasant part of the old dwarven city. The " +
             "walls here are covered with water and strange slime, and in " +
             "the ground is a large, stinking hole.\n");

    add_exit("d2", "east");
    add_item("hole",
             "The hole would probably have been possible to enter if " +
             "it hadn't smelled so awfully. The smell will most likely go " +
             "away any day now.\n");

    add_cmd_item("hole", "enter",
                 "It smells so bad that you decide to stay where you are.\n");
}
