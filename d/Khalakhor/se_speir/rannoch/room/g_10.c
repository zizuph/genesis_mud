/* File         : /d/Khalakhor/se_speir/rannoch/room/g_10.c
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

   add_exit(ROOM + "g_09.c","west",0,4,1);
   add_exit(ROOM + "f_09.c","northwest",0,4,1);
   add_exit(ROOM + "f_10.c","north",0,3,1);
   add_exit(ROOM + "f_11.c","northeast",0,3,1);
   add_exit(ROOM + "g_11.c","east",0,3,1);
   add_exit(ROOM + "h_11.c","southeast",0,3,1);
   add_exit(ROOM + "h_10.c","south",0,3,1);
   add_exit(ROOM + "h_09.c","southwest",0,4,1);

}
