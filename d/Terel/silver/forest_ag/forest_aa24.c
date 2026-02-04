/* File         : /d/Terel/silver/forest/forest_aa24.c
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

    
    add_exit(FOREST_AG + "forest_bb24", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_z24", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa25", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_bb25", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_z25", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_bb23", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_z23", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa23", "west",0,random(4),"@@exits");
    reset_room();
}


