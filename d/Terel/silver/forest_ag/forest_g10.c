/* File         : /d/Terel/silver/forest/forest_g10.c
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

    
    add_exit(FOREST_HP + "forest_h10", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f10", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_g11", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_h11", "northeast",0,random(4),"@@exits");
    add_exit(ROAD + "road12", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_h9", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f9", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_g9", "west",0,random(4),"@@exits");
    reset_room();
}


