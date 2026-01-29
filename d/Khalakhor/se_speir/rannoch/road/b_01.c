/* File         : /d/Khalakhor/se_speir/rannoch/room/b_01.c
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

   set_long(query_long() + "The road continues to the east and southwest.\n");

   add_exit(ROOM + "b_00.c","west",0,1,1);
   add_exit(ROOM + "a_01.c","north",0,1,1);
   add_exit(ROOM + "a_02.c","northeast",0,1,1);
   add_exit(ROAD + "b_02.c","east",0,1,0);
   add_exit(ROOM + "c_02.c","southeast",0,2,1);
   add_exit(ROOM + "c_01.c","south",0,2,1);
   add_exit(ROAD + "c_00.c","southwest",0,1,0);

}
