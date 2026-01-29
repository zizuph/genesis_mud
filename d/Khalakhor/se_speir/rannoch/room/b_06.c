/* File         : /d/Khalakhor/se_speir/rannoch/room/b_06.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-02      
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

   add_exit(ROOM + "b_05.c","west",0,3,1);
   add_exit(ROOM + "a_05.c","northwest",0,3,1);
   add_exit(ROOM + "a_06.c","north",0,3,1);
   add_exit(ROOM + "a_07.c","northeast",0,3,1);
   add_exit(ROOM + "b_07.c","east",0,3,1);
   add_exit(ROAD + "c_07.c","southeast",0,3,1);
   add_exit(ROAD + "c_06.c","south",0,3,1);
   add_exit(ROAD + "c_05.c","southwest",0,3,1);

}
