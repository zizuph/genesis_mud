/* File         : /d/Khalakhor/se_speir/rannoch/room/k_07.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
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

   add_exit(ROOM + "k_06.c","west",0,3,1);
   add_exit(ROOM + "j_06.c","northwest",0,4,1);
   add_exit(ROOM + "j_07.c","north",0,3,1);
   add_exit(ROOM + "j_08.c","northeast",0,3,1);
   add_exit(ROOM + "k_08.c","east",0,3,1);
   add_exit(ROOM + "l_08.c","southeast",0,3,1);
   add_exit(ROOM + "l_07.c","south",0,3,1);
   add_exit(ROOM + "l_06.c","southwest",0,3,1);

}
