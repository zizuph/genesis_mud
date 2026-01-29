/*
 * File:          /d/Avenir/union/room/submissions/a_small_room.c
 * Creator:       Cirion
 * Date:          Wed Jun  3 08:33:10 1998
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/union/npc/asoriana#81080
 * Comments:      
 *                This is a test of the Union NPC Asoriana
 *                creating a room for the Union. Some features
 *                this is testing out: specification of a
 *                particular include file, set_min_items and
 *                set_min_cmd_items, and new proper
 *                indentation.
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("a small room");
    set_long("This is a small, bare room with no noticable "
        + "features. Thick walls for dark masonry constitute "
        + "the surroundings. Shadows lurk everywhere, "
        + "casting a dark pass over head.\n");

    add_item(({"wall"}),
        "It is a normal wall.\n");
    add_item(({"floor","ground"}),
        "The ground is made from large blocks of masonry.\n");
    add_item(({"ceiling"}),
        "It is high overhead.\n");
    add_item(({"sand"}),
        "Sand fills the cracks in the floor.\n");
    add_item(({"wood"}),
        "The wood is old, and contains lovely designs.\n");
    add_item(({"wood"}),
        "The wood is old, and contains lovely designs.\n");
    add_item(({"wood"}),
        "The wood is old, and contains lovely designs.\n");
    add_item(({"wood"}),
        "The wood is old, and contains lovely designs.\n");
    add_item(({"wood"}),
        "The wood is old, and contains lovely designs.\n");
    add_item(({"wood"}),
        "The wood is old, and contains lovely designs.\n");
    add_item(({"wood"}),
        "The wood is old, and contains lovely designs.\n");
    add_cmd_item(({"pool"}),
        ({"drink"}),
        "The water is cool and refreshing.\n");
    add_cmd_item(({"up"}),
        ({"jump"}),
        "You jump happily about.\n");


}
