/* File         : /d/Khalakhor/se_speir/rannoch/room/z_07.c
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

   add_exit(ROOM + "z_06.c","west",0,3,1);
   add_exit(ROOM + "y_06.c","northwest",0,3,1);
   add_exit(ROOM + "y_07.c","north",0,3,1);
   add_exit(ROOM + "y_08.c","northeast",0,3,1);
   add_exit(ROOM + "z_08.c","east",0,3,1);
   add_exit(ROOM + "aa_08.c","southeast",0,3,1);
   add_exit(ROOM + "aa_07.c","south",0,3,1);

}
