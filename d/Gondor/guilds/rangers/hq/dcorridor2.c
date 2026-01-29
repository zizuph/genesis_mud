/*
 *  /d/Gondor/guilds/rangers/hq/dcorridor2.c
 *
 *  A room downstairs in the Central Headquarters hideout
 *
 *  Coded by Alto, 7 July 2001
 *    Original theme of Druedain hideout by Elessar
 *
 *  Modification log:
 *    Gwyneth, 3 May 2004
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
        + "north there appears to be a shop of some sort, while to the south "
        + "you hear dishes and mugs clanking. Mingling with the aroma of food "
        + "wafting in from the south are the strong odours of animals housed "
        + "in captivity. The cages stacked in the room to the west appear to "
        + "be the source. Soft light from adjacent rooms " 
        + "filters in to light your way.\n";
}

void
create_gondor()
{
    set_short("a broad corridor in Central Headquarters");
    set_long(&long_desc());

    add_exit(RANGERS_HQ_DIR + "hq_shop",    "north", 0, 1);
    add_exit(RANGERS_HQ_DIR + "mess_hall",  "south", 0, 1);
    add_exit(RANGERS_HQ_DIR + "post",       "west",  0, 1);
    add_exit(RANGERS_HQ_DIR + "dcorridor1", "east",  0, 1);

    hideout_add_items();

    add_item(({"corridor", "hall", "room"}), &long_desc());
    add_item(({"shop"}), "Why don't you walk to the north and have a "
        + "closer look?\n");
    add_item(({"cage", "cages"}), "There are many cages stacked in the room "
        + "to the west, but you would have to walk closer to see what they "
        + "contain.\n");
    add_item(({"light", "soft light"}), "Torches lit in adjacent rooms "
        + "cast a warm soft light in the corridor.\n");
    add_item(({"rooms", "adjacent rooms"}), "Go closer to get " 
        + "a better look.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

}

