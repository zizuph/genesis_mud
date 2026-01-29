/*
 *  /d/Gondor/guilds/rangers/hq/ucorridor1.c
 *
 *  A room upstairs in the Central Headquarters hideout
 *
 *  Coded by Alto, 21 June 2001
 *    Original theme of Druedain hideout by Elessar
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_HQ_DIR + "ch_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public string      long_desc();


string
long_desc()
{
    if (Tstand->query_torch_is_lit())
    {
        return "You are standing at the north end of the corridor. "
            + "The wooden floor creaks beneath your feet, "
            + "not as a result of poor carpentry, but rather because the "
            + "hideout stands partially in the trees and was built by clever "
            + "hands to shift in the wind. Looking to the west, you see a "
            + "room containing long rows of bunks, while to the east "
            + "is a small room containing a number of strange racks and "
            + "shelves. To the south, you see what appears to be a flight of "
            + "stairs. The room is lit by an iron torch stand mounted on the "
            + "north wall.\n";
    }

    return "You are standing at the north end of the corridor. "
        + "The wooden floor creaks beneath your feet, "
        + "not as a result of poor carpentry, but rather because the hideout "
        + "stands partially in the trees and was built by clever hands "
        + "to shift in the wind. Looking to the west, you see a "
        + "room containing long rows of bunks, while to the east "
        + "is a small room containing a number of strange racks and shelves. "
        + "To the south, you see what appears to be a flight of stairs. "
        + "Without light from the torch stand, it is difficult to see here. "
        + "Hopefully someone will be along soon to replace the torch.\n";
}


void
create_gondor()
{
    set_short("the north end of the corridor");
    set_long(&long_desc());

    add_exit(RANGERS_HQ_DIR + "start",   "west",  0, 1);
    add_exit(RANGERS_HQ_DIR + "armroom", "east",  0, 1);
    add_exit(RANGERS_HQ_DIR + "uphall",  "south", 0, 1);

    hideout_add_items();

    add_item(({"corridor", "hallway", "room"}), &long_desc());
    add_item(({"wall", "walls", "north wall", "wall to the north"}), "There "
        + "is a wall to the north of the "
        + "corridor. The wall, like most things in the "
        + "hideout, is constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions. This wall is also a little warmer "
        + "as a result of the iron torch stand mounted upon it.\n");
    add_item(({"apprentice", "apprentice ranger"}), "You are too late! "
        + "Ranger apprentices are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");
    add_item(({"stairs", "wooden stairs", "flight"}), "Why don't you "
        + "walk south and examine them more closely?\n");
    add_item(({"rows", "bunks", "rows of bunks", "room to the west"}), "The "
        + "many bunks suggest "
        + "that the room to the west is the sleeping quarters for rangers "
        + "stationed at Central Headquarters. You would need to "
        + "walk further west to see them clearly.\n");
    add_item(({"racks", "shelves", "strange racks", "strange shelves"}),
        "They seem to be made for the housing of specialized items. "
        + "You would need to walk further east to see them clearly.\n");

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, &daylight()));

    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &hideout_add_torch());
}

