/* File         : /d/Khalakhor/se_speir/rannoch/room/v_07.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-02      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include "room.h"

inherit FOREST_BASEFILE;

void
create_khalakhor_room()
{
   create_loch_room();

   add_exit(ROOM + "v_06.c","west",0,3,1);
   add_exit(ROOM + "u_06.c","northwest",0,3,1);
   add_exit(ROOM + "u_07.c","north",0,3,1);
   add_exit(ROOM + "u_08.c","northeast",0,3,1);
   add_exit(ROOM + "v_08.c","east",0,3,1);
   add_exit(ROOM + "w_08.c","southeast",0,3,1);
   add_exit(ROOM + "w_07.c","south",0,3,1);
   add_exit(ROOM + "w_06.c","southwest",0,3,1);

}
