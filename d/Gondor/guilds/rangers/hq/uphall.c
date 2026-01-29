/*
 *  /d/Gondor/guilds/rangers/hq/uphall.c
 *
 *  A room upstairs in the Central Headquarters hideout
 *
 *  Coded by Alto, 21 June 2001
 *    Original theme of Druedain hideout by Elessar
 *  Updated Tigerlily, January 20, 2004
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_HQ_DIR + "ch_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public string long_desc();


string
long_desc()
{
    return "You are standing at the head of a sturdy-looking flight "
        + "of wooden stairs. The walls to the east and west are so close "
        + "that you can touch them both from the center of the hallway. "
        + "The wooden floor creaks beneath your feet, "
        + "not as a result of poor carpentry, but rather because the hideout "
        + "stands partially in the trees and was built by clever hands "
        + "to shift in the wind. Looking to the north, you see a "
        + "another corridor running east and west, while to the south "
        + "the hallway continues further into the hideout. "
        + "Warm light filters up from below.\n";
}


void
create_gondor()
{
    set_short("at the top of the stairs");
    set_long(&long_desc());

    add_exit(RANGERS_HQ_DIR + "ucorridor1", "north", 0, 1);
    add_exit(RANGERS_HQ_DIR + "ucorridor2", "south", 0, 1);
    add_exit(RANGERS_HQ_DIR + "boardhall", "down", 0, 1);

    hideout_add_items();

    add_item(({"corridor", "hallway"}), &long_desc());
    add_item(({"wall", "walls"}), "There are two walls here, one to the "
        + "east and one to the west.\n");
    add_item(({"west wall", "wall to the west"}), "The west wall, like most "
        + "things in the "
        + "hideout, is constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions. This wall is also a little warmer "
        + "as a result of the iron torch stand mounted upon it.\n");
    add_item(({"east wall", "wall to the east"}), "The east wall, like most "
        + "things in the "
        + "hideout, is constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions.\n");
    add_item(({"stairs", "wooden stairs", "flight"}), "Wide wooden steps "
        + "descend through a gentle curve to the floor below.\n");
    add_item(({"steps", "step", "wooden steps"}), "The steps are constructed "
        + "from native oak milled from the Druedain forest. The outer edges "
        + "of each step still retain some of their original finish, but "
        + "the middle sections are worn smooth with the passage of many "
        + "booted feet over a large span of years.\n");
    add_item(({"edges", "outer edges", "middle sections"}), "These are "
        + "best viewed in the context of the entire step, don't you think?\n");
    add_item(({"bulletin board", "board"}), "Why don't you go south and "
        + "get a better look?\n");
    add_item(({"floor below"}), "Below you is that part of the hideout open "
        + "to all the free peoples who pass this way. Among them may be those "
        + "interested in becoming rangers themselves someday, so be sure "
        + "to offer the courtesy of Gondor when passing down these stairs.\n"); 

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

}
