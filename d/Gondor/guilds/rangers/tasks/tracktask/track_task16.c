/*
 *  /d/Gondor/guilds/rangers/hq/track_task16.c
 *
 *  A room for the rabbit tracking apprentice task
 *
 *  Coded by Alto, 07 December 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../../rangers.h"

inherit TRACKTASK_DIR + "tracktask_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_gondor()
{
    set_short("On the side of a hill");
    set_long("The path you are following appears to have been made by deer, and "
        + "winds in a slow spiral around the hill. The trees of the forest ring "
        + "the hill and cover the landscape as far as the eye can see. From "
        + "here it looks like you may climb further uphill or go downhill back "
        + "to the forest.\n");

    track_add_items();
    
    add_item(({"hill", "small hill"}), "The hill is largely devoid of trees, "
        + "which makes it seem a bald spot rising out of the surrounding forest. "
        + "Although it bears few trees, brambles are in exceeding supply.\n");
    add_item(({"bramble", "brambles"}), "The brambles choke the side of the "
        + "hill. It would be easy to get tangled up in them and plummet down "
        + "the hard way.\n");
        
    add_exit(TRACKTASK_DIR + "track_task15", "uphill", &allowed(), 1);
    add_exit(TRACKTASK_DIR + "track_task17",  "downhill", &allowed(), 1);

    reset_room();
}
