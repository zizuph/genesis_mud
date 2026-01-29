/* File         : /d/Khalakhor/se_speir/rannoch/room/f_00.c
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

   add_exit(ROOM + "e_00.c","north",0,3,1);
   add_exit(ROOM + "e_01.c","northeast",0,3,1);
   add_exit(ROOM + "f_01.c","east",0,3,1);
   add_exit(ROOM + "g_01.c","southeast",0,3,1);
   add_exit(ROOM + "g_00.c","south",0,3,1);

}
