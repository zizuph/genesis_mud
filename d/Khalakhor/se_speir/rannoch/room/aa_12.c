/* File         : /d/Khalakhor/se_speir/rannoch/room/aa_12.c
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

   add_exit(ROOM + "aa_11.c","west",0,3,1);
   add_exit(ROOM + "z_11.c","northwest",0,3,1);
   add_exit(ROOM + "z_12.c","north",0,3,1);
   add_exit(ROOM + "z_13.c","northeast",0,3,1);
   add_exit(ROOM + "aa_13.c","east",0,3,1);
   add_exit(ROOM + "ab_12.c","south",0,3,1);
   add_exit(ROOM + "ab_11.c","southwest",0,3,1);

}
