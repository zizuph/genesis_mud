/* File         : /d/Khalakhor/se_speir/rannoch/room/e_13.c
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

   add_exit(ROOM + "e_12.c","west",0,3,1);
   add_exit(ROAD + "d_12.c","northwest",0,3,1);
   add_exit(ROOM + "d_13.c","north",0,2,0);
   add_exit(ROOM + "f_13.c","south",0,2,0);
   add_exit(ROOM + "f_12.c","southwest",0,3,1);

}
