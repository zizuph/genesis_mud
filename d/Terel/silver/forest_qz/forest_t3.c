/* File         : /d/Terel/silver/forest/forest_t3.c
 * Creator      : Tomas
 * Date         : August 2000         
 * Purpose      : forest file for Silver Forest.
 * Related Files: /d/Terel/silver/include/forest_base.c
 * Comments     : Basic Silver forest room.
 * Modifications: 
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

    
    add_exit(FOREST_QZ + "forest_u3", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s3", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t4", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u4", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s4", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u2", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s2", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t2", "west",0,random(4),"@@exits");
    reset_room();
}


