/*
 *  This is the base room Halflings guildhouse
 *  Updated by Finwe, September 2015
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "halflings.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>
#include <terrain.h>

inherit "/std/room";
inherit "/d/Faerun/std/room_tell";
inherit "/d/Faerun/std/search";
inherit "/d/Faerun/std/cmd_parse";


void
create_guild_room()
{
}

public void
create_room()
{
    add_item("walls", 
        "The walls are covered with plaster and white. They are textured and " +
        "look clean. Pools of yellow light reflect on them from the candles. " +
        "Sparring dummies line one wall and a wooden plaque is fastened to " +
        "another wall. The windows in the walls are open and let in fresh air.\n");
    add_item(({"ground", "floor"}),
        "The floor is made from dark woods. They are smooth and worn in some " +
        "places. Some mats are spread around and used for training.\n");
    add_item(({"candles"}),
        "The candles are large and made from beeswax. They are golden yellow " +
        "and burn brightly, filling the room with a golden color. Their " +
        "flames flicker in the air, casting shadows across the walls, " +
        "ceiling, and floor.\n");
    add_item(({"ceiling"}),
        "Like the walls, the ceiling is covered with plaster and white. " +
        "Wooden beams support the ceiling and run the width of the room.\n");
    add_item(({"beams"}),
        "The beams are square and cut from large trees. They were stained " +
        "a deep brown and polished to a deep glow. The beams support the " +
        "ceiling and run the width of the room.\n");
    add_item(({"windows"}),
        "The windows are large and set in the walls. They are made from " +
        "glass and are open, letting in fresh air. \n");

    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
//    add_prop(ROOM_I_ALLOW_STEED, 0); // no horsies in the house. They're messy.
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    create_guild_room();
}
