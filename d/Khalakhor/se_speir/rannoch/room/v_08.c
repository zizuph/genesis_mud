/* File         : /d/Khalakhor/se_speir/rannoch/room/v_08.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     : Entrance to the bandit camp
 * Modifications: 
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "room.h"

inherit FOREST_BASEFILE;

int check_cliff();
int climb_cliff();

int 
check_cliff()
{
   int a_skill = TP->query_base_skill(SS_AWARENESS);

   if (a_skill <= 20)
   {
      write("It is a very high cliff, and it is just an "
          + "outcrop of a mountainous region to the east "
          + "and south of here.\n");
   }
   else if (a_skill <= 30)
   {
      write("It is a very high cliff, and it is just an "
          + "outcrop of a mountainous region to the east "
          + "and south of here. At this point, the cliff "
          + "is a bit lower, possibly even low enough for "
          + "you to climb it.\n");
   }
   else if (a_skill <= 50)
   {
      write("It is a very high cliff, and it is just an "
          + "outcrop of a mountainous region to the east "
          + "and south of here. At this point, the cliff "
          + "is rather low, compared to the the rest of "
          + "the wall. It looks climbable, if extra care is "
          + "taken.\n");
   }
   else if (a_skill > 50)
   {
      write("It is a very high cliff, and it is just an "
          + "outcrop of a mountainous region to the east "
          + "and south of here. You can easily see that "
          + "this part of the cliff wall is climbable.\n");
   }

   return 1;
}
  
int
climb_cliff()
{

   int c_skill = TP->query_skill(SS_CLIMB);
   
   if (c_skill <= 20)
   {
      write("The cliff wall is too sheer at this point, you doubt "
          + "you would get far up before falling down again.\n");
   }
   else if (c_skill <= 30)
   {
      write("You climb up the cliff, with great effort.\n");

      say(QCTNAME(this_player())+" starts to climb up the cliff, and "
                    + "though it looks as if " + HE + " is about to "
                    + "fall down a few times, eventually " + HE + " reaches "
                    + "the top");

      TP->move_living("M",ROOM + "s_09",1,0);

      say("You hear a few scraping sounds, and soon you see "
        + "that " + QTNAME(this_player()) + " arrives from "
        + "below by climbing up the cliff.\n");

      TP->add_fatigue(-40);
   }
   else if (c_skill > 30)
   {
      write("You climb up the cliff, easier than you would have thought.\n");

      say(QCTNAME(this_player())+" climbs up the cliff, with little trouble.\n");

      TP->move_living("M",ROOM + "s_09",1,0);

      say("You hear a few scraping sounds, and soon you see "
        + "that " + QTNAME(this_player()) + " arrives from "
        + "below by climbing the cliff.\n");

      TP->add_fatigue(-25);
   }   

   return 1;
}

void
create_khalakhor_room()
{
   create_loch_room();

   add_cmd_item(({"cliffs","cliff","wall","cliff wall"}),
                ({"climb","climb the","scale","scale the",
                  "climb up","climb up the"}),
                  climb_cliff);

   add_cmd_item(({"cliff","cliffs","wall","cliff wall"}),
                ({"exa","examine","look at"}),
                  check_cliff);

   add_exit(ROOM + "v_07.c","west",0,3,1);
   add_exit(ROOM + "u_07.c","northwest",0,3,1);
   add_exit(ROOM + "u_08.c","north",0,3,1);
   add_exit(ROOM + "w_09.c","southeast",0,3,1);
   add_exit(ROOM + "w_08.c","south",0,3,1);
   add_exit(ROOM + "w_07.c","southwest",0,3,1);

    set_long("This is an ancient forest, and no path can be seen. " 
           + "The trees are very old and majestic, reaching far up " 
           + "above you. Heather grows practically everywhere in sight, "
           + "creating a sea of pink and green between the trees and "
           + "around the rocks and shrubs of the forest floor. The "
           + "way east is blocked by high cliffs.\n");

}
