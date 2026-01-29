/* File         : /d/Khalakhor/se_speir/rannoch/room/ac_10.c
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

   add_exit(ROOM + "ad_09.c","west",0,3,1);
   add_exit(ROOM + "ac_09.c","northwest",0,3,1);
   add_exit(ROOM + "ac_10.c","north",0,3,1);
   add_exit(ROOM + "ac_11.c","northeast",0,3,1);
   add_exit(ROOM + "ad_11.c","east",0,3,1);
   add_exit(ROOM + "ae_10.c","south",0,3,1);
   add_exit(ROOM + "ae_09.c","southwest",0,3,1);

}
