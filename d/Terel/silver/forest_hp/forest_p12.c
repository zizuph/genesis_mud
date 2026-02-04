/* File         : /d/Terel/silver/forest/forest_p12.c
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

    
    add_exit(FOREST_QZ + "forest_q12", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o12", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p13", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q13", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o13", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q11", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o11", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p11", "west",0,random(4),"@@exits");
    reset_room();
}


