/* File         : /d/Terel/silver/forest/forest_l18.c
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
  
    add_exit(FOREST_HP + "forest_m18", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k18", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l19", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m19", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k19", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m17", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k17", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l17", "west",0,random(4),"@@exits");
    reset_room();
}


