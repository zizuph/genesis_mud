/* File         : /d/Terel/silver/forest/forest_dd5.c
 * Creator      : Tomas
 * Date         : August 2000         
 * Purpose      : forest file for Silver Forest.
 * Related Files: /d/Terel/silver/include/forest_base.c
 * Comments     : Basic Silver forest room.
 * Modifications: Modified by Pasqua
 */


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit INCLUDE + "forest_base";


public void
create_room()
{
    ::create_room();
    set_short_desc("north");
    set_long_desc(random(10));
	add_my_desc("A tall deviantly large redwood oak.\n");
    
    add_exit(FOREST_AG + "forest_cc5", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_dd6", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_cc6", "southeast",0,random(4),"@@exits");

    add_item(({"oak", "redwood oak", "large redwood oak", "tall oak", "tall redwood oak"}), "Its a deviantly large and tall redwood oak, this must be " +
       "the largest tree in the whole silver forest.\n");
    reset_room();
}



