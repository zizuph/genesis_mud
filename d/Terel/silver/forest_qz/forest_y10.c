/* File         : /d/Terel/silver/forest/forest_y10.c
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

    
    add_exit(FOREST_QZ + "forest_z10", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_x10", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_y11", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_z11", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_x11", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_z9", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_x9", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_y9", "west",0,random(4),"@@exits");
    reset_room();
}


