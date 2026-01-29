/* File         : /d/Khalakhor/se_speir/rannoch/room/a_01.c
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

   add_item(({"river","stream","water"}),
              "Down below flows a river in great haste from the "
            + "mountains down to the sea. It will become wider "
            + "and less rapid the further south it flows, but "
            + "here it would be suicide to attempt a crossing of it.\n");
   add_item(({"ravine"}),
              "Almost straight down from where you stand the "
            + "ravine goes, from the river's eastern bank and as "
            + "far east as you can see. Heavy vegetation grows "
            + "down there, you can not go further that way.\n");
   add_cmd_item(({"ravine","down","down ravine"}),
                  "climb",
                  "The vegetation is too for you to even see the "
                + "sides of the ravine, let alone climbing it.\n");

   add_exit(ROOM + "a_02.c","east",0,3,1);
   add_exit(ROAD + "b_02.c","southeast",0,3,1);
   add_exit(ROAD + "b_01.c","south",0,3,1);
   add_exit(ROOM + "b_00.c","southwest",0,3,1);

   set_short("Ancient woodlands, near a ravine");
   set_long("This is an ancient forest, and no path can be seen. " 
          + "The trees are very old and majestic, reaching far up " 
          + "above you. Heather grows practically everywhere in sight, "
          + "creating a sea of pink and green between the trees and "
          + "around the rocks and shrubs of the forest floor. It is "
          + "impossible to follow the river north here, as your path "
          + "ends in a ravine.\n");
}
