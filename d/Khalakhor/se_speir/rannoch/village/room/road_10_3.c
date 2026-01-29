/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_10_3.c
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
               "You stand on a small pier on the river's eastern "
             + "bank. The river joins the lake south of here, "
             + "and it seems impossible to cross it here due to "
             + "its depth and temperature. On the other side "
             + "you see nothing but forest.\n");
    add_item(({"pier","small pier"}),
               "The pier is very old, but looks sturdy enough to "
             + "walk on without worry. MORE.\n");

    add_exit(ROOM + "road_11_3.c","east",0,1,0);

    set_short("On a small pier");
    set_long("You stand on a small pier in the river, with the "
           + "village east of you. The river rushes on below the "
           + "boards you stand on, passing through the village "
           + "and then joins the lake.\n");
}

