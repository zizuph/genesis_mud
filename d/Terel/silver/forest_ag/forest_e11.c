/* File         : /d/Terel/silver/forest/forest_e11.c
 * Creator      : Tomas
 * Date         : August 2000         
 * Purpose      : forest file for Silver Forest.
 * Related Files: /d/Terel/silver/include/road_base.c
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

    
    add_exit(FOREST_AG + "forest_f11", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d11", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_e12", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f12", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d12", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f10", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d10", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_e10", "west",0,random(4),"@@exits");
    reset_room();
}


