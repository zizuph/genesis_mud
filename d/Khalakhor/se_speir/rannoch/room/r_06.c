/* File         : /d/Khalakhor/se_speir/rannoch/room/r_06.c
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

    add_item(({"cliffs","cliff"}),
               "It is a very high cliff, and it is just an "
             + "outcrop of a mountainous region to the west "
             + "of here.\n");

   add_exit(ROOM + "r_05.c","west",0,3,1);
   add_exit(ROOM + "q_05.c","northwest",0,3,1);
   add_exit(ROOM + "q_06.c","north",0,3,1);
   add_exit(ROOM + "q_07.c","northeast",0,3,1);
   add_exit(ROOM + "r_07.c","east",0,3,1);
   add_exit(ROOM + "s_07.c","southeast",0,3,1);
   add_exit(ROOM + "s_06.c","south",0,3,1);
   add_exit(ROOM + "s_05.c","southwest",0,3,1);

}
