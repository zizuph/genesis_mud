/* File         : /d/Terel/silver/forest/forest_g11.c
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

    
    add_exit(FOREST_HP + "forest_h11", "north",0,random(4),"@@exits");
    add_exit(ROAD + "road12", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_g12", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_h12", "northeast",0,random(4),"@@exits");
    add_exit(ROAD + "road13", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_h10", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f10", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_g10", "west",0,random(4),"@@exits");
    reset_room();
}


