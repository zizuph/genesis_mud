#pragma strict_types

inherit "/d/Kalad/std/room";
#include "/d/Kalad/sys/areas.h"

public void
create_cvan_room()
{
}

// Configure the room
public nomask void
create_kalad_room()
{
    set_area(AREA_KABAL);
    set_district(DISTRICT_CARAVAN);

    set_hear_bell(2);

    create_cvan_room();
}
