/* File         : /d/Terel/silver/forest/forest_bb19.c
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

    
    add_exit(FOREST_AG + "forest_cc19", "north",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa19", "south",0,random(4),"@@exits");
    add_exit(ROAD + "road61", "east",0,random(4),"@@exits");
    add_exit(ROAD + "road62", "northeast",0,random(4),"@@exits");
    add_exit(ROAD + "road60", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_cc18", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_aa18", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_bb18", "west",0,random(4),"@@exits");
    reset_room();
}


