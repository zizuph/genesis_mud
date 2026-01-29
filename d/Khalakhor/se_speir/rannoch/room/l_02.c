/* File         : /d/Khalakhor/se_speir/rannoch/room/l_02.c
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

   add_exit(ROOM + "k_02.c","north",0,3,1);
   add_exit(ROOM + "k_03.c","northeast",0,3,1);
   add_exit(ROOM + "l_03.c","east",0,3,1);
   add_exit(ROOM + "m_03.c","southeast",0,3,1);
   add_exit(ROOM + "m_02.c","south",0,3,1);

}
