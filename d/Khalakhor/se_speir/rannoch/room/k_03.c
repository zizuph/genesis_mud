/* File         : /d/Khalakhor/se_speir/rannoch/room/k_03.c
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

   add_exit(ROOM + "k_02.c","west",0,3,1);
   add_exit(ROOM + "j_02.c","northwest",0,3,1);
   add_exit(ROOM + "j_03.c","north",0,3,1);
   add_exit(ROOM + "j_04.c","northeast",0,3,1);
   add_exit(ROOM + "k_04.c","east",0,3,1);
   add_exit(ROOM + "l_04.c","southeast",0,3,1);
   add_exit(ROOM + "l_03.c","south",0,3,1);
   add_exit(ROOM + "l_02.c","southwest",0,4,1);

}
