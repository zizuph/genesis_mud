/* File         : /d/Khalakhor/se_speir/rannoch/room/h_06.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include "room.h"

inherit HILL_BASEFILE;

void
create_khalakhor_room()
{
   create_loch_room();

   add_exit(ROOM + "h_05.c","west",0,3,1);
   add_exit(ROOM + "g_05.c","northwest",0,3,1);
   add_exit(ROOM + "g_06.c","north",0,5,1);
   add_exit(ROOM + "g_07.c","northeast",0,3,1);
   add_exit(ROOM + "h_07.c","east",0,3,1);
   add_exit(ROOM + "i_07.c","southeast",0,3,1);
   add_exit(ROOM + "i_06.c","south",0,3,1);
   add_exit(ROOM + "i_05.c","southwest",0,3,1);

   set_long(query_long() + "The already steep hill rises even higher "
                         + "to the north, the way to the top.\n");
}
