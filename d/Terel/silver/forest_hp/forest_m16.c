/* File         : /d/Terel/silver/forest/forest_m16.c
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

    
    add_exit(FOREST_HP + "forest_n16", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l16", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m17", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n17", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l17", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n15", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l15", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m15", "west",0,random(4),"@@exits");
    reset_room();
}


