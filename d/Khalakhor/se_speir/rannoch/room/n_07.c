/* File         : /d/Khalakhor/se_speir/rannoch/room/n_07.c
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

   add_exit(ROOM + "n_06.c","west",0,3,1);
   add_exit(ROOM + "m_06.c","northwest",0,3,1);
   add_exit(ROOM + "m_07.c","north",0,3,1);
   add_exit(ROOM + "m_08.c","northeast",0,3,1);
   add_exit(ROOM + "n_08.c","east",0,3,1);
   add_exit(ROOM + "o_08.c","southeast",0,3,1);
   add_exit(ROOM + "o_07.c","south",0,3,1);
   add_exit(ROOM + "o_06.c","southwest",0,3,1);

}
