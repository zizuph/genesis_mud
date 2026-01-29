/*
 * m.c
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
    set_short("room full of mirrors");
    set_long("You are in the middle of a room full of mirrors.\n"+
             "In the background you think that you hear a strange tune.\n");

    add_item(({"mirrors", "mirror"}),
             "You see nothing special, except for the ugly image of yourself.\n");
    add_cmd_item("mirrors", "break", "@@brk");
}

string
brk()
{
    this_player()->heal_hp(-this_player()->query_max_hp()/50);
    return "You crush a mirror. Unfortunately you hurt your hands.\n";
}
