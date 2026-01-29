/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_3_9.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-08      
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
    add_item(({"tavern","pub"}),
               "In what seems to be the largest building of this "
             + "area, you see, hear, and smell the presence of a "
             + "tavern. The building itself looks rather run-down "
             + "on the outside, but you can hear laughter and music "
             + "from the inside. The tavern has two entrances, one "
             + "to the immediate west, and further north on the "
             + "building's east side is another entrance.\n");

    add_exit(ROOM + "inn_02.c","in",0,1,0);
    add_exit(ROOM + "road_3_8.c","north",0,1,0);
    add_exit(ROOM + "road_4_8.c","northeast",0,1,0);
    add_exit(ROOM + "road_4_9.c","east",0,1,0);
    add_exit(ROOM + "road_3_10.c","south",0,1,0);

    set_short("Outside inn");
    set_long("Entrance to inn.\n"
           + "Marketplace NE.\n");
}

