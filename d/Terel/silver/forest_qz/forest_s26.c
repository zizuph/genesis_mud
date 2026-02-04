/* File         : /d/Terel/silver/forest/forest_s26.c
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

    
    add_exit(FOREST_QZ + "forest_t26", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r26", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s27", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t27", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r27", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t25", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r25", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s25", "west",0,random(4),"@@exits");
    reset_room();
}


