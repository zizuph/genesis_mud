/* File         : /d/Khalakhor/se_speir/rannoch/room/v_05.c
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

   add_exit(ROOM + "v_04.c","west",0,3,1);
   add_exit(ROOM + "u_04.c","northwest",0,3,1);
   add_exit(ROOM + "u_05.c","north",0,3,1);
   add_exit(ROOM + "u_06.c","northeast",0,3,1);
   add_exit(ROOM + "v_06.c","east",0,3,1);
   add_exit(ROOM + "w_06.c","southeast",0,3,1);
   add_exit(ROOM + "w_05.c","south",0,3,1);
   add_exit(ROOM + "w_04.c","southwest",0,3,1);

}
