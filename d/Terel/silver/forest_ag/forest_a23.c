/* File         : /d/Terel/silver/forest/forest_a23.c
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

    add_exit(FOREST_AG + "forest_a24", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b23", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b24", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b22", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_a22", "west",0,random(4),"@@exits");

    reset_room();
}


