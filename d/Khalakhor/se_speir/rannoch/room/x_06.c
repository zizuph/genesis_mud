/* File         : /d/Khalakhor/se_speir/rannoch/room/x_06.c
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

   add_exit(ROOM + "w_05.c","northwest",0,3,1);
   add_exit(ROOM + "w_06.c","north",0,3,1);
   add_exit(ROOM + "w_07.c","northeast",0,3,1);
   add_exit(ROOM + "x_07.c","east",0,3,1);
   add_exit(ROOM + "y_07.c","southeast",0,3,1);
   add_exit(ROOM + "y_06.c","south",0,3,1);

}
