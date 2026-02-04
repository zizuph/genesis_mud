/* File         : /d/Terel/silver/forest/forest_d15.c
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
    set_short_desc("south");
    set_long_desc(random(10));

    
    add_exit(FOREST_AG + "forest_e15", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_c15", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d16", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_e16", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_c16", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_e14", "northwest",0,random(4),"@@exits");
    add_exit(ROAD + "road04", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d14", "west",0,random(4),"@@exits");
    reset_room();
}


