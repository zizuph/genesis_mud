/* File         : /d/Terel/silver/forest/forest_z18.c
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
    set_short_desc("north");
    set_long_desc(random(10));

    
    add_exit(FOREST_AG + "forest_aa18", "north",0,random(4),"@@exits");
    add_exit(ROAD + "road56", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_z19", "east",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa19", "northeast",0,random(4),"@@exits");
    add_exit(ROAD + "road57", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa17", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_y17", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_z17", "west",0,random(4),"@@exits");
    reset_room();
}


