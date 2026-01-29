/* File         : /d/Khalakhor/se_speir/rannoch/room/p_07.c
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

   add_exit(ROOM + "p_06.c","west",0,3,1);
   add_exit(ROOM + "o_06.c","northwest",0,3,1);
   add_exit(ROOM + "o_07.c","north",0,3,1);
   add_exit(ROOM + "o_08.c","northeast",0,3,1);
   add_exit(ROOM + "p_08.c","east",0,3,1);
   add_exit(ROOM + "q_08.c","southeast",0,3,1);
   add_exit(ROOM + "q_07.c","south",0,3,1);
   add_exit(ROOM + "q_06.c","southwest",0,3,1);

}
