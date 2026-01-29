/*
 * p5.c
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
    set_short("on the top of a mountain");
    set_long("You are on the top of a small mountain. Deep below you, " +
             "you see a small path leading towards Cadu, the town " +
             "that is visible far away in the horizon. To the south, far " +
             "out in the sea is a small volcano island, and north of you " +
             "a path leads deeper into the mountains.\n");

    add_item("path", "The path is deep below you.\n");
    add_item("island", "The small volcano island is barely visible.\n");

    add_exit("p4", "down");
    add_exit("p6", "north");
}
