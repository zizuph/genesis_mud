/* File         : /d/Khalakhor/se_speir/rannoch/room/d_06.c
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

   add_exit(ROOM + "d_05.c","west",0,3,1);
   add_exit(ROAD + "c_05.c","northwest",0,3,1);
   add_exit(ROAD + "c_06.c","north",0,3,1);
   add_exit(ROAD + "c_07.c","northeast",0,3,1);
   add_exit(ROOM + "d_07.c","east",0,3,1);
   add_exit(ROOM + "e_07.c","southeast",0,4,1);
   add_exit(ROOM + "e_06.c","south",0,4,1);
   add_exit(ROOM + "e_05.c","southwest",0,4,1);

   set_short("Steep woodlands");
   set_long("This is an ancient forest, and no path can be seen. " 
          + "The trees are very old and majestic, reaching far up " 
          + "above you. Heather grows practically everywhere in sight, "
          + "creating a sea of pink and green between the trees and "
          + "around the rocks and shrubs of the forest floor. The land "
          + "rises steeply to the south.\n");
}
