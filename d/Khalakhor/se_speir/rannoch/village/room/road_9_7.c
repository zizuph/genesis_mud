/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_9_7.c
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
    add_item(({"river","water"}),
               "You stand the river's eastern bank. The river joins "
             + "the lake south of here, and it seems impossible to "
             + "cross it here due to its depth and temperature, but "
             + "there is a bridge west of you.\n");

    add_item(({"bridge","crossing"}),
               "The village has been built on both sides of the "
             + "river, and this bridge seems to be the only way "
             + "to cross into the other side. It is made of wood "
             + "and stone, allowing heavy traffic across it.\n");

    add_exit(ROOM + "road_8_7.c","west",0,1,0);
    add_exit(ROOM + "road_9_6.c","north",0,1,0);
    add_exit(ROOM + "road_10_6.c","northeast",0,1,0);
    add_exit(ROOM + "road_10_7.c","east",0,1,0);
    add_exit(ROOM + "road_9_8.c","south",0,1,0);

    set_short("Main road, bridge");
    set_long("Main road starts, goes E.\n"
           + "Bridge W.\n");
}

