/* File         : /d/Khalakhor/se_speir/rannoch/room/c_05.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-02      
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

   set_long(query_long() + "The road continues to the northwest and east.\n");

   add_exit(ROOM + "c_04.c","west",0,1,1);
   add_exit(ROAD + "b_04.c","northwest",0,1,0);
   add_exit(ROOM + "b_05.c","north",0,1,1);
   add_exit(ROOM + "b_06.c","northeast",0,1,1);
   add_exit(ROAD + "c_06.c","east",0,1,0);
   add_exit(ROOM + "d_06.c","southeast",0,2,1);
   add_exit(ROOM + "d_05.c","south",0,2,1);
   add_exit(ROOM + "d_04.c","southwest",0,2,1);

}
