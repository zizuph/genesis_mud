/* File         : /d/Khalakhor/se_speir/rannoch/room/x_09.c
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

   add_exit(ROOM + "x_08.c","west",0,3,1);
   add_exit(ROOM + "w_08.c","northwest",0,3,1);
   add_exit(ROOM + "w_09.c","north",0,3,1);
   add_exit(ROOM + "w_10.c","northeast",0,3,1);
   add_exit(ROOM + "x_10.c","east",0,3,1);
   add_exit(ROOM + "y_10.c","southeast",0,3,1);
   add_exit(ROOM + "y_09.c","south",0,3,1);
   add_exit(ROOM + "y_08.c","southwest",0,3,1);

}
