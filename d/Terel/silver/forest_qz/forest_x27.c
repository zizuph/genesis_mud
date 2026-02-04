/* File         : /d/Terel/silver/forest/forest_x27.c
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
    set_short_desc("north");
    set_long_desc(random(10));

    
    add_exit(FOREST_QZ + "forest_y27", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_w27", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_x28", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_y28", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_w28", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_w26", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_w26", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_x26", "west",0,random(4),"@@exits");
    reset_room();
}


