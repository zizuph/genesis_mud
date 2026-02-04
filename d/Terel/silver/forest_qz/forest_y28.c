/* File         : /d/Terel/silver/forest/forest_y28.c
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
    set_short_desc("north");
    set_long_desc(random(10));

    
    add_exit(FOREST_QZ + "forest_z28", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_x28", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_y29", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_z29", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_x29", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_z27", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_x27", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_y27", "west",0,random(4),"@@exits");
    reset_room();
}


