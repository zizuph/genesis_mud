/* File         : /d/Terel/silver/forest/forest_s18.c
 * Creator      : Tomas
 * Date         : August 2000         
 * Purpose      : forest file for Silver Forest.
 * Related Files: /d/Terel/silver/include/road_base.c
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
    
    add_exit(FOREST_QZ + "forest_t18", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r18", "south",0,random(4),"@@exits");
    add_exit(ROAD + "road47", "east",0,random(4),"@@exits");
    add_exit(ROAD + "road48", "northeast",0,random(4),"@@exits");
    add_exit(ROAD + "road46", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t17", "northwest",0,1);
    add_exit(FOREST_QZ + "forest_r17", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s17", "west",0,random(4),"@@exits");
    reset_room();
}


