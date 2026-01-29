/* File:          /d/Khalakhor/ship/macdunn/std/sea_base.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       The sea base room, inherited by all other
 *                sea rooms from Port Macdunn.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/room";
#include "../local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"

public void
create_sea()
{
}

public void
create_khalakhor_room()
{
    set_short("in the sea");
    set_long("   In the sea.\n");

    add_item("water","The water stretches in every direction.\n");
    add_item("sky","The grey cloudy sky above offers no hope.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(OBJ_I_LIGHT, 2);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_OCEAN);

    create_sea();
}
