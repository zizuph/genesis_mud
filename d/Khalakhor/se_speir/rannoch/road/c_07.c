/* File         : /d/Khalakhor/se_speir/rannoch/room/c_07.c
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

   add_exit(ROAD + "c_06.c","west",0,1,0);
   add_exit(ROOM + "b_06.c","northwest",0,1,1);
   add_exit(ROOM + "b_07.c","north",0,1,1);
   add_exit(ROOM + "b_08.c","northeast",0,1,1);
   add_exit(ROAD + "c_08.c","east",0,1,0);
   add_exit(ROOM + "d_08.c","southeast",0,2,1);
   add_exit(ROOM + "d_07.c","south",0,2,1);
   add_exit(ROOM + "d_06.c","southwest",0,2,1);

   clone_here(NPC + "ciara")->move(this_object());

}
