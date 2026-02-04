/* File         : /d/Terel/silver/forest/forest_m1.c
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

    
    add_exit(FOREST_HP + "forest_n1", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l1", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m2", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n2", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l2", "southeast",0,random(4),"@@exits");
   
    reset_room();
}


