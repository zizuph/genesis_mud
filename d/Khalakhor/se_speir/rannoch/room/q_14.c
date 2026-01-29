/* File         : /d/Khalakhor/se_speir/rannoch/room/s_09.c
 * Creator      : Darragh@Genesis
 * Date         : 01-04-02         
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "room.h"

inherit "/d/Khalakhor/std/room";

public void
create_khalakhor_room()
{
    set_short("A room");
    set_long("Bläh.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(ROOM + "p_13.c","northwest",0,1,0);
    add_exit(ROOM + "p_15.c","northeast",0,1,0);
    add_exit(ROOM + "r_14.c","south",0,1,0);

}
