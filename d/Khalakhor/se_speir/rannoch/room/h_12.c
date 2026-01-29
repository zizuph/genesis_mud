/* File         : /d/Khalakhor/se_speir/rannoch/room/h_12.c
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

   add_exit(ROOM + "h_11.c","west",0,3,1);
   add_exit(ROOM + "g_11.c","northwest",0,3,1);
   add_exit(ROOM + "g_12.c","north",0,2,0);
   add_exit(ROOM + "i_11.c","southwest",0,2,0);

}
