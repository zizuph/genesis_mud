/**********************************************************************
 * - sea_base.c                                                     - *
 * - Sea base room                                                  - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Undated by Damaris@Genesis 05/2005                             - *
 **********************************************************************/
#pragma strict_types

inherit "/d/Khalakhor/std/room";
#include "local.h" 
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"

public void
create_sea()
{
}

public void
create_khalakhor_room()
{
    set_short("The open sea");
    set_long("The open sea.\n");

    add_item(({"water", "waters","crystal waters","clear waters"}),
      "The water is cold but surprisingly pure and clean.\n");
    add_item(({"sky"}),
      "The sky is full of large billowing clouds.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_OCEAN);

    create_sea();
}
