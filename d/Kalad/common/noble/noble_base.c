/*
    /d/Kalad/common/noble/noble_base.c

    Noble district base room.
    
    Fysix@Genesis, March 1998
 */
#pragma strict_types
#pragma save_binary
    
inherit "/d/Kalad/std/room";

#include "/d/Kalad/sys/areas.h"

public void
create_noble_room()
{
}

// Configure the room
public nomask void
create_kalad_room()
{
    set_area(AREA_KABAL);
    set_district(DISTRICT_NOBLE);

    create_noble_room();
}

// Add a sky item
// Might implement some more weather dependent sky later
void
add_sky()
{
    add_item("sky", "The sky is grey and clouded.\n");
}
