#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

#define BLACK_RIDER_ROOM	"/d/Gondor/morgul/blackrider"

public void
create_roads() 
{
    set_street("overgrown, stone paved road");
    set_where("southeast");
    set_county("Dunland");
    set_land("old Gondor");
    set_mountain("Misty Mountains");
    set_vegetation("lush blue green tall grass");
    set_extraline("You are in a valley leading down to a river to the "
      + "southeast, perhaps the river Angren. In all directions, the "
      + Vegetation+" covers the land of "+County+". A road is running "
      + "in from the northwest and down a steep slope towards the "
      + "river, southeast. A road of stone, recently repaired, runs "
      + "north up the valley alongside the river.");

    add_exit(DUN_DIR+"road/r02","northwest", 0, 5);
    add_exit(DUN_DIR+"ford/f04","southeast", 0, 5);
    add_exit(ISEN_DIR+"isenroad/isenroad1","north", 0, 3);

    FIX_EUID
    BLACK_RIDER_ROOM->load_me();
}

