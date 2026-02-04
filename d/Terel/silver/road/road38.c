/* File         : /d/Terel/silver/forest/road38.c
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

	set_short("a road in the middle of the silver forest");
	add_exit(ROAD + "road39", "north", 0);
	add_exit(ROAD + "road37", "east", 0);
	add_exit(FOREST_HP + "forest_o15", "west",0,random(4),"@@exits");
	add_exit(FOREST_HP + "forest_n16", "south",0,random(4),"@@exits");

    reset_room();
}
