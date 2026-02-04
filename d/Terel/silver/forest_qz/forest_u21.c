/* File         : /d/Terel/silver/forest/forest_u21.c
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
    set_short_desc("middle");
    set_long_desc(random(10));

    
    add_exit(FOREST_QZ + "forest_v21", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t21", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u22", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_v22", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t22", "southeast",0,random(4),"@@exits");
    add_exit(ROAD + "road51", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t20", "southwest",0,random(4),"@@exits");
    add_exit(ROAD + "road50", "west",0,random(4),"@@exits");
    reset_room();
}


