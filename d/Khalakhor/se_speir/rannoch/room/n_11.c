/* File         : /d/Khalakhor/se_speir/rannoch/room/n_11.c
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

   add_exit(ROOM + "n_10.c","west",0,3,1);
   add_exit(ROOM + "m_10.c","northwest",0,2,0);
   add_exit(ROOM + "o_11.c","south",0,2,0);
   add_exit(ROOM + "o_10.c","southwest",0,3,1);

}
