/* File         : /d/Terel/silver/forest/forest_g13.c
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

    add_exit(FOREST_HP + "forest_h13", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f13", "south",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_g14", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_h14", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f14", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_h12", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f12", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_g12", "west",0,random(4),"@@exits");
    reset_room();
}


