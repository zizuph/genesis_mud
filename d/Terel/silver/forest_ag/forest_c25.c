/* File         : /d/Terel/silver/forest/forest_c25.c
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

    
    add_exit(FOREST_AG + "forest_d25", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b25", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_c26", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d26", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b26", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d24", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_b24", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_c24", "west",0,random(4),"@@exits");
    reset_room();
}


