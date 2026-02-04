/* File         : /d/Terel/silver/forest/forest_r14.c
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

    
    add_exit(FOREST_QZ + "forest_s14", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q14", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r15", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s15", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q15", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s13", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q13", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r13", "west",0,random(4),"@@exits");
    reset_room();
}


