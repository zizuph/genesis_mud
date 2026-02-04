/* File         : /d/Terel/silver/forest/forest_b5.c
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

    add_exit(FOREST_AG + "forest_c5", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_a5", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b6", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b4", "west",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_c6", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_a6", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_c4", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_a4", "southwest",0,random(4),"@@exits");
    reset_room();
}


