/* File         : /d/Khalakhor/se_speir/rannoch/room/aa_09.c
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

   add_exit(ROOM + "aa_08.c","west",0,3,1);
   add_exit(ROOM + "z_08.c","northwest",0,3,1);
   add_exit(ROOM + "z_09.c","north",0,3,1);
   add_exit(ROOM + "z_10.c","northeast",0,3,1);
   add_exit(ROOM + "aa_10.c","east",0,3,1);
   add_exit(ROOM + "ab_10.c","southeast",0,3,1);
   add_exit(ROOM + "ab_09.c","south",0,3,1);
   add_exit(ROOM + "ab_08.c","southwest",0,3,1);

}
