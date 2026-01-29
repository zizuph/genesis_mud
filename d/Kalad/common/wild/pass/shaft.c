/* 
 * /d/Kalad/common/wild/pass/shaft.c
 * Purpose    : Player can climb up to top.c, of they might fail if their climb skill is slow, down to w6.c
 * Located    : Caravan Route
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
/* by Antharanos */
void
create_room()
{
   add_prop(ROOM_I_INSIDE,1);
   set_short("Inside the cave");
   set_long("You are inside the cave, halfway between the ground and "+
      "a distant light far above.\n");
   add_item(({"ground"}),"Its very far down from here.\n");
   add_item(({"light"}),"It seems like just a tiny pinprick of light, "+
      "but it serves you as a guide to help you on your way.\n");
}
void
init()
{
   ::init();
   
   add_action("try_climb", "climb");
}

int
try_climb(string str)
{
   notify_fail("Climb up or down?\n");
   
   if (!str)
      return 0;
   
   if (str == "up")
      {
      
      if (this_player()->query_skill(SS_CLIMB) < (20 + random(30)))
      {
         write("You start to climb but slip and fall all the way down "+
            "and hurt yourself.\n");
         say(QCTNAME(this_player()) + " starts to climb the rock face but "+
            "slips and falls all the way down.\n");
         this_player()->heal_hp(-200);
         
         tell_room("/d/Kalad/common/wild/pass/w6", "Suddenly you hear a lot of "+
            "noise from above and " + QTNAME(this_player()) + " falls " +
            "down with a bone-crushing sound!\n");
         
         this_player()->move_living("M", "/d/Kalad/common/wild/pass/w6",1);
         return 1;
       }
      
      this_player()->move_living("climbing up the rock face", "/d/Kalad/common/wild/pass/top",1);
      return 1;
   }
   
   if (str == "down")
      {
      set_dircmd("down");
      this_player()->move_living("climbing down", "/d/Kalad/common/wild/pass/w6");
      return 1;
   }
   
   return 0;
}
