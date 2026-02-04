/* File         : /d/Terel/silver/forest/forest_r19.c
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
    set_short_desc("south");
    set_long_desc(random(10));
    
    add_exit(FOREST_QZ + "forest_s19", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q19", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r20", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s20", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q20", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s18", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q18", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r18", "west",0,random(4),"@@exits");
    reset_room();
}


