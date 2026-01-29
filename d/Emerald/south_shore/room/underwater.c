/* /d/Emerald/south_shore/room/underwater.c
 * 
 *  Demerga's kill room. When the player is close to death, 
 *  they are transported into this room to die in.
 *
 *  Created 9.4.2022 by Velith
 */

#pragma strict_types
#include <stdproperties.h>
#include <time.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include <subloc.h>
#include <money.h>
inherit "/d/Emerald/std/room";
inherit LIBPIER;
#define WATER_SUBL "_water_subloc"

/* prototypes */
public void         create_emerald_room();


/*
 * Function nane:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("The watery depths of Lake Telberin");
    set_long("A mysterious location underneath the waves of "
             + "Lake Telberin.\n");
    add_prop(ROOM_I_INSIDE, 10000);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_subloc(WATER_SUBL, this_object());
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_TELEPORT, 1);
} /* create_emerald_room */
