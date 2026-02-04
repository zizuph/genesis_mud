/* File         : /d/Terel/silver/forest/forest_u29.c
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
    set_short_desc("middle");
    set_long_desc(random(10));

    
    add_exit(FOREST_QZ + "forest_v29", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t29", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u30", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_v30", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t30", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_v28", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t28", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u28", "west",0,random(4),"@@exits");
    reset_room();
}


