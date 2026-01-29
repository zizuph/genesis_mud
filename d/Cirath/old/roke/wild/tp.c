/*
 * tp.c
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
    set_noshow_obvious(1);
    set_short("top of mountain");
    set_long("You are on top of the mountain. The view is breathtaking, " +
             "and the valleys below you look wonderful, at least when " +
             "you don't think of climbing back down to them. The ground " +
             "is rather soft here, and traces of a huge fire is clearly " +
             "visible. " +
             "You notice a very beautiful crystal stairway leading up " +
             "through the clouds. " +
             "There are two obvious exits: down and north.\n");

    add_item("ground",
             "It is very soft, with occasional pieces of coal on it.\n");
    add_item("fire",
             "The fire is not really a fire any longer, just some coal pieces.\n");
    add_item("coal", "Normal, black, a little sticky pieces of coal.\n");

    add_exit("q3", "down");
    add_exit("", "up", "@@blst");
    add_exit("q4", "north");

    add_item("stairway", "It looks like the stairway to heaven.\n");
}

int
blst()
{
    write("You slip on the crystal and fall back down again.\n");
    return 1;
}
