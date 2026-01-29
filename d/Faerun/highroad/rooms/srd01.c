/*
 * Trail in the Grasslands near the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include "/d/Faerun/sys/mudtime.h";
#include "/d/Faerun/sys/sunlight.h"
#include <stdproperties.h>
#include <terrain.h>

//inherit HIGH_RD_DIR + "std/base_road.c";
inherit BASE_ROAD;

#define MIN_AWARE   30

//public string describe();

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("an old stone road");

    set_long(long_desc);
    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_std_herbs("meadow");

    room_add_object("/d/Genesis/obj/donation/column");

    add_exit(HR_DIR + "nrd01", "northwest");
    add_exit(FARM2_DIR + "rd01", "northeast");
    add_exit(HR_DIR + "srd02", "southeast");
    add_exit(HR_DIR + "str02", "west");

}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}

/*
 * Function name:        describe
 * Description  :        provide the long description for the room with
 *                       awareness-dependant results
 * Returns      :        string - the text for set_long()
 */
public string
long_desc()
{
    ::long_desc();
    string  desc;

    desc = CAP(query_short()) +  ". " + TIME_DESC_ROOM + " The old stone road " +
        "runs through the grassland. It runs north and south past bushes and trees. " +
        "There appears to be a small trail leading west from the road.";
/*
    if (this_player()->query_skill(SS_AWARENESS) >= MIN_AWARE)
    {
        desc += "There appears to be a small trail leading west from the road.";
    }
*/
    return desc + "\n";
} /* describe */
