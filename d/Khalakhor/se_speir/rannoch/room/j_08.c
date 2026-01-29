/* File         : /d/Khalakhor/se_speir/rannoch/room/j_08.c
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

   add_exit(ROOM + "j_07.c","west",0,3,1);
   add_exit(ROOM + "i_07.c","northwest",0,4,1);
   add_exit(ROOM + "i_08.c","north",0,4,1);
   add_exit(ROOM + "i_09.c","northeast",0,3,1);
   add_exit(ROOM + "j_09.c","east",0,3,1);
   add_exit(ROOM + "k_09.c","southeast",0,3,1);
   add_exit(ROOM + "k_08.c","south",0,3,1);
   add_exit(ROOM + "k_07.c","southwest",0,3,1);

}
