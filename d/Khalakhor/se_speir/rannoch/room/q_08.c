/* File         : /d/Khalakhor/se_speir/rannoch/room/q_08.c
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

   add_item(({"cliffs","cliff","wall","cliff wall"}),
              "It is a very high cliff, and it is just an "
            + "outcrop of a mountainous region to the east "
            + "and south of here.\n");

   add_cmd_item(({"cliff","cliffs","wall"}),"climb",
            "The cliff wall is too sheer at this point, you doubt "
          + "you would get far up before falling down again.\n");

   add_exit(ROOM + "r_07.c","southwest",0,3,1);
   add_exit(ROOM + "q_07.c","west",0,3,1);
   add_exit(ROOM + "p_07.c","northwest",0,3,1);
   add_exit(ROOM + "p_08.c","north",0,3,1);
   add_exit(ROOM + "p_09.c","northeast",0,3,1);

    set_long("This is an ancient forest, and no path can be seen. " 
           + "The trees are very old and majestic, reaching far up " 
           + "above you. Heather grows practically everywhere in sight, "
           + "creating a sea of pink and green between the trees and "
           + "around the rocks and shrubs of the forest floor. The "
           + "way east and south is blocked by high cliffs.\n");

}
