/* This file is /d/Gondor/olorin/farm/farm/stable2.c       */
/* It belongs to a small farm in the Ered Nimrais          */	
/* Olorin, Nov 1992                                        */

inherit "/std/room";
#include "/d/Gondor/common/lib/time.c"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("A dark and damp cellar");
    set_long("You are in a dark and damp cellar. The walls are made of " +
        "earth, in a few places reinforced with wooden beams. The floor is " +
        "just earth stamped flat. You wonder for what purpose the farmer dug " +
        "this hole under his stable since it seems to be quite empty " +
        "and since it is definitely too damp to store provisions here.\n");
/*
    add_exit(FARM_DIR + "farm/stable2", "up", 0);
*/
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,0);
    clone_object(FARM_DIR + "farm/trapdoor2")->move(this_object());
}
