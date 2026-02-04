/* File         : /d/Terel/silver/forest/forest_p16.c
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

    
    add_exit(FOREST_QZ + "forest_q16", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o16", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p17", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q17", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o17", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q15", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o15", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p15", "west",0,random(4),"@@exits");
    reset_room();
}


