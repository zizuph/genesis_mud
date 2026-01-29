/* File         : /d/Khalakhor/se_speir/rannoch/room/b_04.c
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

   set_long(query_long() + "The road continues to the west and southeast.\n");

   add_exit(ROAD + "b_03.c","west",0,1,0);
   add_exit(ROOM + "a_03.c","northwest",0,1,1);
   add_exit(ROOM + "a_04.c","north",0,1,1);
   add_exit(ROOM + "a_05.c","northeast",0,1,1);
   add_exit(ROOM + "b_05.c","east",0,1,1);
   add_exit(ROAD + "c_05.c","southeast",0,1,0);
   add_exit(ROOM + "c_04.c","south",0,1,1);
   add_exit(ROOM + "c_03.c","southwest",0,1,1);

}
