/*
 *  /d/Gondor/guilds/rangers/ambush/ambush_1a.c
 *
 *  A path leading to an ambush/vantage spot for the rangers
 *
 *  Coded by Alto, 05 August 2001
 *
 *  Modification log:
 *   Gwyneth, 3 May 2004
 *  Fixed west exit. pointed to a closed room
 *   Finwe, Feb. 2007
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
    set_long(long_desc() + "You can also return to the road.\n");

    ambush_add_cmds();
    ambush_add_items();
    set_ambush_move(RANGERS_AMB_DIR + "ambush_1b");
    add_prop(ROOM_M_NO_SCRY, 1);

// Goes to a room that was closed years ago and then connects to Old Bree
// -- Finwe, February 2007
//    add_exit(ARNOR_DIR + "greenway/nr1", "west", check_amb_move, 2, 0);

    add_exit(ARNOR_DIR + "greenway/nr3", "west", check_amb_move, 2, 0);
}

