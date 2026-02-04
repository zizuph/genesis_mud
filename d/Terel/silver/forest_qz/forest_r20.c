/* File         : /d/Terel/silver/forest/forest_r20.c
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

    
    add_exit(FOREST_QZ + "forest_s20", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q20", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_r21", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s21", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_q21", "southeast",0,random(4),"@@exits");
    add_exit(ROAD + "road47", "northwest",0,random(4),"@@exits");
    add_exit(ROAD + "road45", "southwest",0,random(4),"@@exits");
    add_exit(ROAD + "road46", "west",0,random(4),"@@exits");
    reset_room();
}


