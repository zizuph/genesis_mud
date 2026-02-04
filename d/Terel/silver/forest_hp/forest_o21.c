/* File         : /d/Terel/silver/forest/forest_o21.c
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
    set_short_desc("middle");
    set_long_desc(random(10));


    
    add_exit(FOREST_HP + "forest_p21", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n21", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o22", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p22", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n22", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p20", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n20", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o20", "west",0,random(4),"@@exits");
    reset_room();
}


