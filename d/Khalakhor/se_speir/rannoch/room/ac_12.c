/* File         : /d/Khalakhor/se_speir/rannoch/room/ac_12.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include "room.h"

inherit RIVERSIDE_BASEFILE;

void
create_khalakhor_room()
{
   create_loch_room();

   add_item(({"river","rapid river","stream","water"}),
              "This river rushes in from the eastern "
            + "mountains, on its way south towards the sea. "
            + "It is only about fifteen feet wide, but "
            + "you see no possibility of crossing it, "
            + "since it is not only rapid, deep, and "
            + "probably icy cold, but also too far down.\n");

   add_exit(ROOM + "ac_11.c","west",0,3,1);
   add_exit(ROOM + "ab_11.c","northwest",0,3,1);
   add_exit(ROOM + "ab_12.c","north",0,3,1);
   add_exit(ROOM + "ad_11.c","southwest",0,3,1);


}
