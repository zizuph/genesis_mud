/* File         : /d/Terel/silver/forest/road20.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : road file for Silver Forest.
 * Related Files: /d/Terel/silver/include/road_base.c
 * Comments     : Basic Silver forest road room.
 * Modifications: 
 */


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit INCLUDE + "road_base";


public void
create_room()

{
    ::create_room();

	set_short("a road near the middle of the silver forest");
    add_exit(ROAD + "road19", "west", 0);
    add_exit(ROAD + "road21", "south", 0);
	add_exit(FOREST_HP + "forest_h16", "north",0,random(4),"@@exits");

    reset_room();
}
