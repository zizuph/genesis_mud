/* File         : /d/Terel/silver/forest/forest_v27.c
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

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit INCLUDE + "forest_base";


public void
create_room()
{
    ::create_room();
    set_short_desc("north");
    set_long_desc(random(10));

	add_item("bushes", "Its something about these bushes.\n");
    add_cmd_item("bushes", "squeeze through", "@@hidden@@");
    
    add_exit(FOREST_QZ + "forest_w27", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_w28", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_w26", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u26", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_v26", "west",0,random(4),"@@exits");
    reset_room();
}

int
hidden()
{
    if((TP->query_skill(SS_AWARENESS) + TP->query_skill(SS_LOC_SENSE) +
         random(100) > 100))
        {
            TP->move_living("by entering the bushes", "/w/pasqua/goblincave/cave01");

            return 1;
        }
    write("You try to enter the rough bushes, but can't seem to find the proper way.\n");
    TP->add_fatigue(-15);
    say(QCTNAME(this_player()) + " looks for an opening in the bushes, but doesn't find any.\n");
    return 1;
}

