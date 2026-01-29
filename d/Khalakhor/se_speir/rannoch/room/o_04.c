/* File         : /d/Khalakhor/se_speir/rannoch/room/o_04.c
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

   add_exit(ROOM + "o_03.c","west",0,3,1);
   add_exit(ROOM + "n_03.c","northwest",0,3,1);
   add_exit(ROOM + "n_04.c","north",0,3,1);
   add_exit(ROOM + "n_05.c","northeast",0,3,1);
   add_exit(ROOM + "o_05.c","east",0,3,1);
   add_exit(ROOM + "p_05.c","southeast",0,3,1);
   add_exit(ROOM + "p_04.c","south",0,3,1);
   add_exit(ROOM + "p_03.c","southwest",0,3,1);

}
