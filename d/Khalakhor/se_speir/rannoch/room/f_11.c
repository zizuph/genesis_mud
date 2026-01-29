/* File         : /d/Khalakhor/se_speir/rannoch/room/f_11.c
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

   add_exit(ROOM + "f_10.c","west",0,3,1);
   add_exit(ROOM + "e_10.c","northwest",0,3,1);
   add_exit(ROOM + "e_11.c","north",0,3,1);
   add_exit(ROOM + "e_12.c","northeast",0,3,1);
   add_exit(ROOM + "f_12.c","east",0,3,1);
   add_exit(ROOM + "g_12.c","southeast",0,3,1);
   add_exit(ROOM + "g_11.c","south",0,3,1);
   add_exit(ROOM + "g_10.c","southwest",0,3,1);

}
