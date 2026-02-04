/* File         : /d/Terel/silver/forest/forest_bb16.c
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
    set_short_desc("north");
    set_long_desc(random(10));

    
    add_exit(FOREST_AG + "forest_cc16", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa16", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_bb17", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_cc17", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa17", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_cc15", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa15", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_bb15", "west",0,random(4),"@@exits");
    reset_room();
}


