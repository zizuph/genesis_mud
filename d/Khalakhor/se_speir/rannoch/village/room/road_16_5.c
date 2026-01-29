/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_16_5.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-19      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Changed structure to coord system (Darragh 2003-07-25) 
 */

#pragma strict_types

#include "room.h"

inherit VILLAGE_BASEFILE;

public void
create_road()
{
    add_item(({"alley","alleway","narrow alley"}),
               "It looks like any alley, common here among the closely "
             + "built houses. But this one seems to go a bit longer, "
             + "just north of you.\n");
    add_item(({"cliff","cliffs","cliffside","cliffsides","rocks"}),
               "MAYBE.\n");

    add_exit(ROOM + "road_17_6.c","southeast",0,1,0);
    add_exit(ROOM + "road_16_6.c","south",0,1,0);
    add_exit(ROOM + "road_16_4.c","north",0,1,1);

    set_long("MAYBE cliff sealing off.\n"
           + "MAYBE special alley.\n");
}

