/* File         : /d/Terel/silver/forest/forest_q24.c
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

    
    add_exit(FOREST_QZ + "forest_r24", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p24", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q25", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r25", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p25", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r23", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p23", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q23", "west",0,random(4),"@@exits");
    reset_room();
}


