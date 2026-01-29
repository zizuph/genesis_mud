/* File         : /d/Khalakhor/se_speir/rannoch/room/j_01.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-02      
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

   add_exit(ROOM + "i_01.c","north",0,3,1);
   add_exit(ROOM + "i_02.c","northeast",0,3,1);
   add_exit(ROOM + "j_02.c","east",0,3,1);
   add_exit(ROOM + "k_02.c","southeast",0,3,1);

}
