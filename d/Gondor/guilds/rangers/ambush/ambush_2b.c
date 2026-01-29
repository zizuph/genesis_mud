/*
 *  /d/Gondor/guilds/rangers/ambush/ambush_2b.c
 *
 *  A path leading to an ambush/vantage spot for the rangers
 *
 *  Coded by Alto, 05 August 2001
 *  Modification log:
 *   Gwyneth, 4 May 2004
 */
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include "../rangers.h"

inherit "/d/Gondor/std/room.c";
inherit RANGERS_AMB_DIR + "ambush_funcs.c";

void
create_gondor()
{
    ambush_extraline();

    set_short("following a hidden path");
    set_long(long_desc());

    ambush_add_cmds();
    add_prop(ROOM_M_NO_SCRY, 1);
    ambush_add_items();

    set_ambush_move(RANGERS_AMB_DIR + "ambush_2c");
}
