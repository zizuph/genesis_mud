/* File         : /d/Terel/silver/forest/forest_j29.c
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

    
    add_exit(FOREST_HP + "forest_k29", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_i29", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_j30", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k30", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_i30", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k28", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_i28", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_j28", "west",0,random(4),"@@exits");
    reset_room();
}


