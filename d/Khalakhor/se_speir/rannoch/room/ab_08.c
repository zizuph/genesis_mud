/* File         : /d/Khalakhor/se_speir/rannoch/room/ab_08.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
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

   add_exit(ROOM + "aa_07.c","northwest",0,3,1);
   add_exit(ROOM + "aa_08.c","north",0,3,1);
   add_exit(ROOM + "aa_09.c","northeast",0,3,1);
   add_exit(ROOM + "ab_09.c","east",0,3,1);
   add_exit(ROOM + "ac_09.c","southeast",0,3,1);
   add_exit(ROOM + "ac_08.c","south",0,3,1);

}
