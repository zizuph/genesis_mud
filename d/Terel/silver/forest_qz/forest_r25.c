/* File         : /d/Terel/silver/forest/forest_r25.c
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
    set_short_desc("south");
    set_long_desc(random(10));
	add_my_desc("You notice a small cave to the east.\n");

    
	add_exit(FOREST_QZ + "forest_s25", "north",0,random(4),"@@exits");
	add_exit(FOREST_QZ + "forest_q25", "south",0,random(4),"@@exits");
	add_exit(FOREST_QZ + "forest_s24", "northwest",0,random(4),"@@exits");
	add_exit(FOREST_QZ + "forest_q24", "southwest",0,random(4),"@@exits");
	add_exit(FOREST_QZ + "forest_r24", "west",0,random(4),"@@exits");
	add_exit(RED_DRAGON_LAIR,"east",0); 
    reset_room();
}


