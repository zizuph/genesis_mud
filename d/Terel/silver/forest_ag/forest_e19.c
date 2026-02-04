/* File         : /d/Terel/silver/forest/forest_e19.c
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

    
    add_exit(FOREST_AG + "forest_f19", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d19", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_e20", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f20", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d20", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f18", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d18", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_e18", "west",0,random(4),"@@exits");
    reset_room();
}


