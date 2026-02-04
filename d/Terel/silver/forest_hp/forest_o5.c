/* File         : /d/Terel/silver/forest/forest_o5.c
 * Creator      : Tomas
 * Date         : August 2000         
 * Purpose      : forest file for Silver Forest.
 * Related Files: /d/Terel/silver/include/forest_base.c
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

    
    add_exit(FOREST_HP + "forest_p5", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n5", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o6", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p6", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n6", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n4", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o4", "west",0,random(4),"@@exits");
    reset_room();
}


