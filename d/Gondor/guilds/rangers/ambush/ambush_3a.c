/*
 *  /d/Gondor/guilds/rangers/ambush/ambush_3a.c
 *
 *  A path leading to an ambush/vantage spot for the rangers
 *
 *  Coded by Alto, 05 August 2001
 *  Modification log:
 *   Gwyneth, 4 May 2004
 *
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <stdproperties.h>

inherit "/d/Gondor/std/room.c";
inherit RANGERS_AMB_DIR + "ambush_funcs.c";

void
create_gondor()
{
    ambush_extraline();

    set_short("following a hidden path");
    set_long(long_desc() + "You can also return to the road.\n");

    ambush_add_cmds();
    ambush_add_items();
    add_prop(ROOM_M_NO_SCRY, 1);

    set_ambush_move(RANGERS_AMB_DIR + "ambush_3b");
    add_exit(ITH_DIR + "road/er7", "south", check_amb_move, 2, 0);
}
