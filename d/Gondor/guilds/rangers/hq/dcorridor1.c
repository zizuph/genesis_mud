/*
 *  /d/Gondor/guilds/rangers/hq/dcorridor1.c
 *
 *  A room downstairs in the Central Headquarters hideout
 *
 *  Coded by Alto, 7 July 2001
 *    Original theme of Druedain hideout by Elessar
 *
 *  Modification log:
 *    Updated Tigerlily, January 18, 2004
 *    Gwyneth, 3 May 2004
 *
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
    return "You are standing in a broad corridor. Strong oak beams support "
        + "the ceiling, and oak panels make up the walls of the hall. To the "
        + "east you see a large bulletin board, and to the north there is a "
        + "large room filled with books. The corridor continues further into "
        + "the hideout to the west. Soft light from adjacent rooms " 
        + "filters in to light your way.\n";
}


void
create_gondor()
{
    set_short("a broad corridor in Central Headquarters");
    set_long(&long_desc());

    add_exit(RANGERS_LIBRARY + "hq_library", "north", 0, 1);
    add_exit(RANGERS_HQ_DIR  + "boardhall",  "east", 0, 1);
    add_exit(RANGERS_HQ_DIR  + "dcorridor2", "west", 0, 1);

    hideout_add_items();

    add_item(({"corridor", "hall", "room"}), &long_desc());
    add_item(({"board", "bulletin board"}), "Why don't you walk to the "
        + "east and have a closer look?\n");
    add_item(({"books", "library"}), "Why don't you walk to the north and "
        + "have a closer look?\n");
    add_item(({"light", "soft light"}), "Torches lit in adjacent rooms "
        + "cast a warm soft light in the corridor.\n");
    add_item(({"rooms", "adjacent rooms"}), "Go closer to get " 
        + "a better look.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
}

