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
inherit HERBSEARCH;

public void
create_khalakhor_room()
{
    set_short("A room");
    set_long("Bläh.\n");

    add_exit(ROOM + "s_12.c","west",0,1,0);
    add_exit(ROOM + "r_14.c","northeast",0,1,0);
    add_exit(ROOM + "s_14.c","east",0,1,0);
    add_exit(ROOM + "t_14.c","southeast",0,1,0);

}
