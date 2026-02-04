/* File         : /d/Terel/silver/forest/forest_bb20.c
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
    set_short_desc("north");
    set_long_desc(random(10));

    
    add_exit(FOREST_AG + "forest_cc20", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa20", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_bb21", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_cc21", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa21", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_cc19", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa19", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_bb19", "west",0,random(4),"@@exits");
    reset_room();
}


