/* File         : /d/Khalakhor/se_speir/rannoch/room/p_05.c
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

   add_exit(ROOM + "p_04.c","west",0,3,1);
   add_exit(ROOM + "o_04.c","northwest",0,3,1);
   add_exit(ROOM + "o_05.c","north",0,3,1);
   add_exit(ROOM + "o_06.c","northeast",0,3,1);
   add_exit(ROOM + "p_06.c","east",0,3,1);
   add_exit(ROOM + "q_06.c","southeast",0,3,1);
   add_exit(ROOM + "q_05.c","south",0,3,1);
   add_exit(ROOM + "q_04.c","southwest",0,3,1);

}
