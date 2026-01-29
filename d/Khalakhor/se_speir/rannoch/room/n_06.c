/* File         : /d/Khalakhor/se_speir/rannoch/room/n_06.c
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

   add_exit(ROOM + "n_05.c","west",0,3,1);
   add_exit(ROOM + "m_05.c","northwest",0,3,1);
   add_exit(ROOM + "m_06.c","north",0,3,1);
   add_exit(ROOM + "m_07.c","northeast",0,3,1);
   add_exit(ROOM + "n_07.c","east",0,3,1);
   add_exit(ROOM + "o_07.c","southeast",0,3,1);
   add_exit(ROOM + "o_06.c","south",0,3,1);
   add_exit(ROOM + "o_05.c","southwest",0,3,1);

}
