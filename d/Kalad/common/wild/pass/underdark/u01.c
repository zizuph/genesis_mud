/* 
 * /d/Kalad/common/wild/pass/underdark/u01.c
 * Purpose    : A mountain room.  Has a random check for climb skill.
 * Located    : 
 * Created By : Antharanos 
 * Modified By: Rico 14.Mar.97 
 */ 

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
#include <ss_types.h>

#define HARD_TO_CLIMB   50
#define DAMAGE          (100 + random(50))
#define THIS_DIR(path)  "/d/Kalad/common/wild/pass/path"

string long;

create_room()
{
   ::create_room();

   set_short("\nOutcropping");
   set_long("\nYou are on an outcropping of the moutainside.\n"+
      "This narrow ledge is barely large enough to hold you. Gazing "+
      "down you can see the tops of the giant redwood trees lying "+
      "dozens of feet below you. Above there is yet more of the magnif"+
      "icent mountainside.\n\n");

   add_item(({ "narrow ledge", "ledge" }), "A small, flat area on the side "+
      "of this mountain. You'd best be careful or you just might fall off!\n");
   add_item(({ "tops", "redwood trees", "redwood tree", "trees", "tree"}),
      "Even from this great height they look quite impressive. The forest "+
      "stretches out of sight to the southwest.\n");
   add_item(({ "southwest", "forest" }), "All you see are more trees... and "+
      "darkness beyond.\n");
   add_item(({ "mountainside", "side", "mountain" }), "The sheer side of the "+
      "mountain you are trying to climb doesn't look as though it gets any "+
      "easier on the way up. However, going down looks just as precarious.\n");

   add_prop(ROOM_NO_TIME_DESC, 1);

   add_exit(THIS_DIR(w39), "down", 0, 2);
   add_exit(THIS_DIR(underdark/u2), "up", "@@climb", 3);
}

void
init()
{
   ::init();

   write("A gust of mountain wind blows against you.\n");
   say("A gust of mountain wind blows against " + QTNAME(TP) + ".\n");
}

climb()
{
   if(TP->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
   {
      write("You slip while trying to scale the mountainside and slam "+
         "into the outcropping!\n");
      TP->heal_hp(-DAMAGE);
      say(QCTNAME(TP) + " slipped while trying to scale the mountainside "+
         "and slammed into the outcropping! " + QCTNAME(TP) + " looks rather "+
         "shaken and bewildered.\n");

      return 1;

      if (TP->query_hp() < 1)
         TP->do_die(TO);
   }

   write("You manage to scale the mountainside.\n");
   say(QCTNAME(TP) + " manages to scale the mountainside.\n");

   return 0;
}

