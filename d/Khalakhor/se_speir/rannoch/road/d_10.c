/* File         : /d/Khalakhor/se_speir/rannoch/room/d_10.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */


#pragma strict_types

#include "room.h"

inherit ROAD_BASEFILE;

void
create_khalakhor_room()
{
   create_loch_room();

   set_long(query_long() + "The road continues to the west and east.\n");

   add_exit(ROAD + "d_09.c","west",0,1,0);
   add_exit(ROOM + "c_09.c","northwest",0,1,1);
   add_exit(ROOM + "c_10.c","north",0,1,1);
   add_exit(ROOM + "c_11.c","northeast",0,1,1);
   add_exit(ROAD + "d_11.c","east",0,1,0);
   add_exit(ROOM + "e_11.c","southeast",0,1,1);
   add_exit(ROOM + "e_10.c","south",0,1,1);
   add_exit(ROOM + "e_09.c","southwest",0,2,1);

}
