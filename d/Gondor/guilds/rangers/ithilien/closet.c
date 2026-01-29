/*
 *  /d/Gondor/guilds/rangers/ithilien/closet.c
 *  another store room, to clean up
 */
inherit "/std/room";

#include "../rangers.h"

#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "exit.c"

object bin, janitor, chute;

void
reset_room()
{
    if (!objectp(janitor))
    {
         janitor = clone_object(RANGERS_NPC + "janitor");
         janitor->move(TO, 1);
         janitor->command("emote enters and pushes a large " +
             "broom around the room to tidy up.");
    }
    if (!objectp(chute))
    {
        chute = clone_object(RANGERS_OBJ + "trash_chute");
        chute->move(TO, 1); 
    }
    if (!objectp(bin))
    {
        bin = clone_object(RANGERS_OBJ + "old_bin");
        bin->move(TO, 1); 
    }
}

public void 
create_room() 
{ 

    FIX_EUID;

    set_short("storage closet");
    set_long("The closet is bare except for a large storage " +
        "bin and a round hole placed in the rock wall. " +
        "\n");
    add_item(({"wall", "walls", "floor", "rock wall"}), "The walls " + 
        "and floor are bare and devoid of decoration. This room is for " +
        "utility purposes only in order to keep the living quarters " +
        "of the rangers tidy.\n");
    add_item("closet", &long());
    reset_room();
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_M_NO_SCRY, 1);
    add_exit((RANGERS_ITH_DIR + "train"), "south", &check_ranger(1));

}

