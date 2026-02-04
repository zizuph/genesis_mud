/* File         : /d/Terel/silver/forest/forest_e25.c
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

    
    add_exit(FOREST_AG + "forest_f25", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d25", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_e26", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f26", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d26", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f24", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_d24", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_e24", "west",0,random(4),"@@exits");
    reset_room();
}


