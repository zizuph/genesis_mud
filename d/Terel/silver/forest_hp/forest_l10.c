/* File         : /d/Terel/silver/forest/forest_l10.c
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

    
    add_exit(FOREST_HP + "forest_m10", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k10", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l11", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m11", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k11", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m9", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k9", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l9", "west",0,random(4),"@@exits");
    reset_room();
}


