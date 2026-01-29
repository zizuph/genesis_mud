/*
 *  /d/Gondor/guilds/rangers/ambush/test_road2.c
 *
 *  A road room for testing the ambush entrances
 *
 *  Coded by Alto, 03 May 2001
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


void
create_gondor()
{
    set_short("A place somewhere in the middle of nowhere.");
    set_long("This is a road. You have no idea where it leads or how "
        + "you got here. Perhaps there is something interesting about "
        + "it, perhaps not.\n");

    add_item(({"place", "road"}), "There doesn't seem to be anything "
        + "particularly appealing about that and your attention quickly "
        + "slips away from it.\n");

    add_exit(RANGERS_AMB_DIR + "test_road1", "north");


    reset_room();
}
