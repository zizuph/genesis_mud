/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_7_6.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-08      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     : Too disgusting?
 * Modifications: Changed structure to coord system (Darragh 2003-07-25) 
 */

#pragma strict_types

#include "room.h"

inherit VILLAGE_BASEFILE;

public void
create_road()
{
    add_item(({"bridge","crossing"}),
               "The village has been built on both sides of the "
             + "river, and this bridge is the only way to cross "
             + "into the other side. It is made of wood and stone, "
             + "allowing heavy traffic across it.\n");
    add_item(({"river","water"}),
               "You stand at the river's western bank. The river joins " 
             + "the lake south of here, and the only means of crossing it "
             + "is the bridge southeast of you.\n");
    add_item(({"garbage","trash","ground","floor","road","path","dirt"}),
               "All the way down to the river the garbage completely "
             + "covers the ground. Rotten remains of fish, fruit and "
             + "meat along with moldy bread and excrement produces an "
             + "awful smell.\n");
      
    add_exit(ROOM + "road_6_6.c","west",0,1,0);
    add_exit(ROOM + "road_7_7.c","south",0,1,0);

    set_short("Along the village wall");
    set_long(query_long() + "The village wall is to your north, where "
                          + "it ends at the riverbank. This place is "
                          + "obviously where most villagers throw away "
                          + "their garbage, and the stench is horrible.\n");
}

