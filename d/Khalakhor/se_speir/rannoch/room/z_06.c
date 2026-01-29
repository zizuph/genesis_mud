/* File         : /d/Khalakhor/se_speir/rannoch/room/z_06.c
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

   add_exit(ROOM + "y_06.c","north",0,3,1);
   add_exit(ROOM + "y_07.c","northeast",0,3,1);
   add_exit(ROOM + "z_07.c","east",0,3,1);
   add_exit(ROOM + "aa_07.c","southeast",0,3,1);

}
