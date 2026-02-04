/* File         : /d/Terel/silver/forest/forest_m9.c
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
    set_short_desc("middle");
    set_long_desc(random(10));

    
    add_exit(FOREST_HP + "forest_n9", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l9", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m10", "east",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n10", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l10", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_n8", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_l8", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_m8", "west",0,random(4),"@@exits");
    reset_room();
}


