/* File         : /d/Khalakhor/se_speir/rannoch/room/b_08.c
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

   add_item(({"ravine"}),
              "Almost straight down from where you stand the "
            + "ravine runs, continuing northwards. Heavy "
            + "vegetation grows down there, you can not go "
            + "that way.\n");

   add_cmd_item(({"ravine","down","down ravine"}),
                  "climb",
                  "The vegetation is too for you to even see the "
                + "sides of the ravine, let alone climbing it.\n");

   add_exit(ROOM + "b_07.c","west",0,3,1);
   add_exit(ROOM + "a_07.c","northwest",0,3,1);
   add_exit(ROOM + "a_08.c","north",0,3,1);
   add_exit(ROOM + "b_09.c","east",0,3,1);
   add_exit(ROOM + "c_09.c","southeast",0,3,1);
   add_exit(ROAD + "c_08.c","south",0,3,1);
   add_exit(ROAD + "c_07.c","southwest",0,3,1);

   set_short("Ancient woodlands, near a ravine");
   set_long("This is an ancient forest, and no path can be seen. " 
          + "The trees are very old and majestic, reaching far up " 
          + "above you. Heather grows practically everywhere in sight, "
          + "creating a sea of pink and green between the trees and "
          + "around the rocks and shrubs of the forest floor. It is "
          + "impossible to go northeast, as the forest drops "
          + "into a ravine.\n");
}
