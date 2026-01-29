/* File         : /d/Khalakhor/se_speir/rannoch/room/m_10.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include "room.h"

inherit SHORE_BASEFILE;

void
create_khalakhor_room()
{
   create_loch_room();

    add_item(({"dock","small dock","simple dock","wooden dock"}),
               "A simple wooden dock, just long enough for a "
             + "few small boats to dock.\n");

   add_exit(ROOM + "m_09.c","west",0,3,1);
   add_exit(ROOM + "l_09.c","northwest",0,2,0);
   add_exit(ROOM + "m_11.c","east",0,2,0);
   add_exit(ROOM + "n_11.c","southeast",0,2,0);
   add_exit(ROOM + "n_10.c","south",0,3,1);
   add_exit(ROOM + "n_09.c","southwest",0,3,1);

   set_long(query_long() + "You see small dock just east of here.\n");
}
