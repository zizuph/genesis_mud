/*
 * red_r4.c
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
    set_short("road through slum districts");
    set_long("This is a filthy road leading through the slum districts " +
             "of Cadu. Around you you spot decayed, old buildings, " +
             "equally decayed people and heaps of trash. A foul smell " +
             "reaches your nose, and you recognise it as the scent of " +
             "goblins.\n");

    add_item("people", "They look very poor.\n");
    add_item("trash", "It looks like half-rotten food.\n");
    add_item("buildings", "Once they were very luxurous, now you almost " +
             "have to pay people to live there.\n");

    add_exit("red_r3", "north");
    add_exit("red_r5", "south");
}
