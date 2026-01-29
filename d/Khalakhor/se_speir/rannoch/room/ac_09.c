/* File         : /d/Khalakhor/se_speir/rannoch/room/ac_09.c
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

   add_exit(ROOM + "ac_08.c","west",0,3,1);
   add_exit(ROOM + "ab_08.c","northwest",0,3,1);
   add_exit(ROOM + "ab_09.c","north",0,3,1);
   add_exit(ROOM + "ab_10.c","northeast",0,3,1);
   add_exit(ROOM + "ac_10.c","east",0,3,1);
   add_exit(ROOM + "ad_10.c","southeast",0,3,1);
   add_exit(ROOM + "ad_09.c","south",0,3,1);
   add_exit(ROOM + "ad_08.c","southwest",0,3,1);

}
