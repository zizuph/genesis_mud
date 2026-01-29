inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <macros.h>
/* by Antharanos */
void
create_room()
{
   object carpet;
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Outskirts of the Bedellin camp");
   set_long("You are at the outskirts of the Bedellin camp, the camp "+
      "lying just to the east. Your immediate surroundings are clear of "+
      "the ever-present sand, and above you, the clear desert sky is "+
      "dominated by the harsh brilliance of the Kaladian sun. Only the "+
      "whistling of the desert wind reaches your ear.\n");
   add_item(({"bedellin camp","camp"}),"A large collection of tents "+
      "gathered about one large central tent.\n");
   add_item(({"tents","tent"}),"They are all clustered about the central "+
      "tent.\n");
   add_item(({"large central tent","large tent","central tent"}),"It rises "+
      "far above the others, indicating its importance. Most likely, it is the "+
      "residence of the sheik of the nomad tribe.\n");
   add_item(({"clear desert sky","clear sky","desert sky","sky"}),
      "Not a cloud can be seen in the blue expanse above you.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_exit(CPASS(desert/camp/c22),"east",0,2);
   carpet = clone_object("/d/Kalad/common/wild/pass/desert/carpet/carpet");
   carpet -> move(TO);
}
come_and_go(which)
{
   object oncarpet,realcarpet;
   oncarpet=present("carpet",TO);
   if(which==0&&!oncarpet) { /* 0 = arriving, 1 = leaving */
      oncarpet = clone_object("/d/Kalad/common/wild/pass/desert/carpet/carpet");
      oncarpet->move(CPASS(desert/carpet/carpet_board));
      tell_room(TO,
         "The flying carpet arrives from the heavens. Now you may board it, for it "+
         "may leave at any moment.\n");
      return 1;
   }
   if(which==1&&oncarpet) {
      realcarpet=present("carpet",TO);
      "secure/master"->do_debug("destroy",realcarpet);
      tell_room(TO,
         "The flying carpet leaves skyward.\n");
      return 1;
   }
}
