/* File         : /d/Terel/silver/forest/forest_j27.c
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

    
    add_exit(FOREST_HP + "forest_k27", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_i27", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_j28", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k28", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_i28", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_k26", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_i26", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_j26", "west",0,random(4),"@@exits");
    reset_room();
}


