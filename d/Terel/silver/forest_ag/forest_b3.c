/* File         : /d/Terel/silver/forest/forest_b3.c
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

    
    add_exit(FOREST_AG + "forest_c3", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_a3", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b4", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b2", "west",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_c4", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_a4", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_c2", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_a2", "southwest",0,random(4),"@@exits");
    reset_room();
}


