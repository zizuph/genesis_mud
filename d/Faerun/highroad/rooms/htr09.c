/*
 * Trail in the hills near the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

//inherit HIGH_RD_DIR + "std/base_road.c";
inherit BASE_ROAD;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("a rocky trail");
    set_extraline("The trail winds through the mountains. Wisps of snow blow across the trail, dusting the rocks and boulders. A chill wind blows down from the mountain.");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is a thin line that wanders through the mountains. It's littered with rocks and draped in snow.\n");
    add_item(({"cliff"}),
        "The cliff has been sheared off and drops down below. It looks like you can probably climb down it.\n");
    
    reset_faerun_room();

    add_sword_mts_cold();

    add_exit(HR_DIR + "htr10", "northeast");

    add_cmd_item(({"down", "cliff", "face", "ridges"}),"climb","@@climb");


}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
}

int climb()
{
    TP->move_living("climbing down the face of the cliff.", HR_DIR + "htr08");
    return 1;
   
}