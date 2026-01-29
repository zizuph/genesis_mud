/* Vladimir 8-10-94 */

#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

object orc;

void reset_room();

void
create_room()
{
    set_short("Bunk room");
    set_long("In this room many orcs receive rest. The bunks are empty\n"
             + "at the moment though. Other than the bunks the room is\n"
             + "more or less empty. Occasionally you may catch an orc \n"
             + "getting ready to doze off to sleep.\n");
    add_item(({"bunks", "beds"}),
             "These bunks are little more than wooden boards stacked "+
             "on top of each other. They smell about as bad as their "+

             "owners.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("hall1", "west");

    reset_room();
}

void
reset_room()
{
    if(!orc)
    {
        orc = clone_object(S_LOCAL_NPC_DIR + "orc2");
        orc->arm_me();
        orc->move_living("xxx", TO);
    }
}

