/*
 *  /d/Gondor/guilds/rangers/ithilien/passage4.c
 *
 * Modification log:
 * 20-Jul-2001,Alto: more tidy up, change inheritance for new
 *                   rangers.
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "exit.c"

public void    reset_room();

object  gRanger;

void
create_gondor()
{
    set_short("A dark winding passage");
    set_long("You are in a dark and narrow passage, with walls rough and "
        + "uneven. A set of stone steps descend into the dark passage here, "
        + "while the passage continues east. It is quite cold and dark "
        + "here.\n");

    add_exit(RANGERS_ITH_DIR + "passage3", "down", &check_ranger(0, gRanger));
    add_exit(RANGERS_ITH_DIR + "passage5", "east", &check_ranger(0, gRanger));
    add_item("walls","They are rough and unevenly cut.\n");
    add_item("passage","The passage continues in darkness east, but you see "
        + "a little light to the north.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_M_NO_SCRY, 1);
    reset_room();
}

void
reset_room()
{
    if (!gRanger)
        gRanger = clone_npc(gRanger, (RANGERS_NPC +"ith_ranger"));
}

