/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_13_5.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-19      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Changed structure to coord system (Darragh 2003-07-25) 
 */

#pragma strict_types

 
#include "room.h"
inherit "/d/Khalakhor/std/room";

void
create_add_items()
{
    add_item(({"house","houses","building","buildings","wall","walls"}),
               "All you see of the houses around you are their back walls "
             + "or possibly side walls. The buildings themselves are made "
             + "of grey wood, and you see no doors or other openings.\n");
    add_item(({"ground","floor","path","mud"}),
               "The ground slopes gently westwards down the hill, and "
             + "here it is quite wet. Some garbage has been dumped "
             + "in this secluded alley, mostly along the walls.\n");
    add_item(({"garbage","trash","litter","pile","piles"}),
               "All sorts of garbage has been accumulated here, and "
             + "almost none of it is organic.\n");

    add_exit(ROOM + "road_14_4.c","northeast",0,1,0);
}
void
create_room_tells()
{
    add_tell(({"A faint smell of something rotten rises from the ground.\n",
               "A faint smell of something moldy rises from a nearby trash "
             + "pile.\n", 
               "A rat scurries among the garbage.\n",
               "You hear footsteps behind you.\n",
               "You hear the cries of birds from the south.\n",}));
}
public void
create_khalakhor_room()
{
    set_short("Alley");
    set_long("NE.\n"); 
}

