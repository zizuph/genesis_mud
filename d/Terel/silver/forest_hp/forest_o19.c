/* File         : /d/Terel/silver/forest/forest_o19.c
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

    
    add_exit(ROAD + "road44", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n19", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_o20", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_p20", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n20", "southeast",0,random(4),"@@exits");
    add_exit(ROAD + "road43", "northwest",0,random(4),"@@exits");
    add_exit(ROAD + "road35", "southwest",0,random(4),"@@exits");
    add_exit(ROAD + "road36", "west",0,random(4),"@@exits");
    reset_room();
}


