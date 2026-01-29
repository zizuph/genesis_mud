/* File         : /d/Khalakhor/se_speir/rannoch/room/d_12.c
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

   set_long(query_long() + "The road continues to the northeast and west.\n");

   add_exit(ROAD + "d_11.c","west",0,1,0);
   add_exit(ROOM + "c_11.c","northwest",0,1,1);
   add_exit(ROOM + "c_12.c","north",0,1,1);
   add_exit(ROAD + "c_13.c","northeast",0,1,0);
   add_exit(ROOM + "d_13.c","east",0,1,1);
   add_exit(ROOM + "e_13.c","southeast",0,1,1);
   add_exit(ROOM + "e_12.c","south",0,1,1);
   add_exit(ROOM + "e_11.c","southwest",0,1,1);

}
