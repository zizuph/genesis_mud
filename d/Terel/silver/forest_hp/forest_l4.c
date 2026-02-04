/* File         : /d/Terel/silver/forest/forest_l4.c
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
    set_short_desc("middle");
    set_long_desc(random(10));

    
    add_exit(FOREST_HP + "forest_m4", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k4", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l5", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m5", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k5", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m3", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k3", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l3", "west",0,random(4),"@@exits");
    reset_room();
}


