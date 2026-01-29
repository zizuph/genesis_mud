/*
 * d4.c
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
    set_short("A cosy stone chamber");
    set_long("You are standing in a stone chamber inside a huge mountain.\n" +
             "The walls have been polished by skilled dwarf craftsmen to " +
             "the smoothness of silk, and then dwarven artists have placed " +
             "expensive mithril decorations in the stone.\n");

    add_item("decorations",
             "The decorations tells a strange tale about dragons, earth and fire.\n");
    add_item("walls",
             "The walls are covered with expensive mithril decorations.\n");

    add_exit("d2", "north");
    add_exit("c1", "south");
}
