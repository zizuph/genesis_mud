/* File         : /d/Terel/silver/forest/road62.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : road file for Silver Forest.
 * Related Files: /d/Terel/silver/include/road_base.c
 * Comments     : Basic Silver forest road room.
 * Modifications: Udana - added caravan function.
 */


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit INCLUDE + "road_base";


public void
create_room()

{
    ::create_room();

    set_short("a road in the northern silver forest");
	set_long(query_long() + "To the north, you see a Cornerstone.\n");
	add_exit(ROAD + "road62", "south", 0);
	add_exit("/d/Terel/common/road/forest_edge", "north", 0);
	add_exit(FOREST_AG + "forest_dd19", "west",0,random(4),"@@exits");
 	add_exit(FOREST_AG + "forest_dd21", "east",0,random(4),"@@exits");   

    reset_room();
}
