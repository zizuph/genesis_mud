/* File         : /d/Terel/silver/forest/forest_u4.c
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

    
    add_exit(FOREST_QZ + "forest_v4", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t4", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u5", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_v5", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t5", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_v3", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u3", "west",0,random(4),"@@exits");
    reset_room();
}


