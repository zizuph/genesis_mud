/* File         : /d/Terel/silver/forest/forest_l29.c
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

    
    add_exit(FOREST_HP + "forest_m29", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k29", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l30", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m30", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k30", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m28", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k28", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l28", "west",0,random(4),"@@exits");
    reset_room();
}


