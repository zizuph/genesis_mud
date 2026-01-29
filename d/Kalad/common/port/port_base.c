/*
    /d/Kalad/common/port/port_base.c

    Port district base room.

    In your port district rooms do a set_hear_bell(1) if the
    room is outside. Inside you won't hear anything because
    the port district is down the cliff and by the sea.

    Fysix@Genesis, March 1998
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Kalad/std/room";
#include "/d/Kalad/sys/areas.h"

public void
create_port_room()
{
}

// Configure the room
public nomask void
create_kalad_room()
{
    set_area(AREA_KABAL);
    set_district(DISTRICT_PORT);

    set_hear_bell(1);

    create_port_room();
}

// Add a sky item
// Might implement some more weather dependent sky later
void
add_sky()
{
    add_item("sky", "The sky is grey and clouded.\n");
}
