/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_15_5.c
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
    add_item(({"building"}),
               "It is a low building with three chimneys and a strong "
             + "door, which is open. A sign hangs above the door.\n");
    add_item(({"door","doorway","dark wood"}),
               "A sturdy door made of a dark wood, reinforced with "
             + "iron.\n");
    add_item(({"sign","hammer","anvil","branch","gnarly branch"}),
               "The sign is made of a gnarly branch with a flat piece of "
             + "wood hanging from it. A picture of a hammer and an anvil "
             + "has been engraved in the wood.\n");
    add_item(({"chimney","chimneys"}),
               "The chimneys on the roof of the building to the north are "
             + "made of stone, and two of them are belching forth smoke.\n");
    add_item(({"smoke"}),
               "The smoke rises from the chimneys and into the sky.\n");

    add_exit(ROOM + "road_15_6.c","south",0,1,0);
    add_exit(ROOM + "smith_forge.c","in",0,1,0);

}

