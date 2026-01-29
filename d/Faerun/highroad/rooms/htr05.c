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
//    add_prop(OBJ_S_SEARCH_FUN, "search_boulder");
//    add_prop(OBJ_I_SEARCH_TIME, 3);

    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("a rocky trail");
    set_extraline("Large boulders and rocks are scattered across the trail. The trail dips down into the hills, hiding your view of the surrounding area.");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is a thin line that wanders through the mountains. It " +
        "is littered with rocks which hide it from casual travellers.\n");
//    add_item(({"large boulder"}),
//        "The boulder is twice as tall as a yeti and several times as " +
//        "wide as a barrel. It's cracked and jagged partially buried in " +
//        "the dirt.\n");

    reset_faerun_room();

    add_grasslands();
    add_hills1();

    add_exit(HR_DIR + "htr06", "northeast");
    add_exit(HR_DIR + "htr04", "south");

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
//
//public string
//search_boulder(object me, string arg)
//{
//    if (arg != "large boulder" )
//	    return "";
//
//    if (this_player()->query_skill(SS_AWARENESS) < 30)
//	    return "";
//
//    add_exit(HR_DIR + "mtr06", "northeast");
//    set_alarm(12.0,0.0,"remove_exit","northeast");
//    return "You search the the large boulder and find a rocky trail " +
//        "going around it.\n";
//}
