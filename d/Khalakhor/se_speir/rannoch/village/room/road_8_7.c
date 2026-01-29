/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_8_7.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-19      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Changed structure to coord system (Darragh 2003-07-25) 
 */

#pragma strict_types

#include "room.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"

inherit VILLAGE_BASEFILE;

int climb_bridge();

int
climb_bridge()
{
   write("You do not have the have skills it take to climb down "
         + "the bridge.\n");
 
   say(QCTNAME(this_player())+ " looks thoroughly at the sides of "
                             + "the bridge, as if considering "
                             + "something.\n");
   return 1;
}
public void
create_road()
{ 
    add_item(({"river","stream","flow"}),
               "The river is what provides the lake with water, "
             + "coming in from the sea far away. Here it joins the "
             + "lake, and tracing its route you finally lose sight "
             + "of it as it meanders away between the forest on "
             + "its west side, and the mountains on the east.\n");

    add_item(({"bridge","crossing"}),
               "The village has been built on both sides of the " 
             + "river, and this bridge seems to be the only way "
             + "to cross into the other side. It is made of wood "
             + "and stone, allowing heavy traffic across it.\n");

    add_cmd_item("bridge","climb",climb_bridge);

    add_exit(ROOM + "road_7_7.c","west",0,1,0);
    add_exit(ROOM + "road_9_7.c","east",0,1,0);

    set_short("On the bridge");
    set_long("You are standing on the bridge between the two halves "
           + "of the village. To the west lies the common areas, "
           + "with the marketplace and shops. To the east lies the "
           + "main living areas, situated on high ground. The river "
           + "that flows beneath you meanders in from the north and "
           + "roars southwards into the lake.\n");
}


