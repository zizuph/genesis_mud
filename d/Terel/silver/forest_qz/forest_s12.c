/* File         : /d/Terel/silver/forest/forest_s12.c
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

    
    add_exit(FOREST_QZ + "forest_t12", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r12", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s13", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t13", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r13", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t11", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r11", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s11", "west",0,random(4),"@@exits");
    reset_room();
}


