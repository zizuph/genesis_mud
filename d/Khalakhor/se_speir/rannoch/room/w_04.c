/* File         : /d/Khalakhor/se_speir/rannoch/room/w_04.c
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

   add_exit(ROOM + "v_03.c","northwest",0,3,1);
   add_exit(ROOM + "v_04.c","north",0,3,1);
   add_exit(ROOM + "v_05.c","northeast",0,3,1);
   add_exit(ROOM + "w_05.c","east",0,3,1);

}
