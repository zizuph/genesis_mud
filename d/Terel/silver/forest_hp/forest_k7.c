/* File         : /d/Terel/silver/forest/forest_k7.c
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

    
    add_exit(FOREST_HP + "forest_l7", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_j7", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k8", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l8", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_j8", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l6", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_j6", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k6", "west",0,random(4),"@@exits");
    reset_room();
}


