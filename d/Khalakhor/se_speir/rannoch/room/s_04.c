/* File         : /d/Khalakhor/se_speir/rannoch/room/s_04.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-02      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include "room.h"

inherit RIVERSIDE_BASEFILE;

void
create_khalakhor_room()
{
   create_loch_room();

   add_exit(ROOM + "r_04.c","north",0,3,1);
   add_exit(ROOM + "r_05.c","northeast",0,3,1);
   add_exit(ROOM + "s_05.c","east",0,3,1);
   add_exit(ROOM + "t_05.c","southeast",0,3,1);
   add_exit(ROOM + "t_04.c","south",0,3,1);
   add_exit(ROOM + "t_03.c","southwest",0,3,1);

}
