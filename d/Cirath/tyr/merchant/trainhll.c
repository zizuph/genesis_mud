/* training.c: Tyr training room: Serpine, 9/12/95. */
 
inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"


void
reset_room()
{
    bring_room_mob("Errlog", TYR_NPC+"trainer.c", 1, 1);
}
 
void
create_room()
{
  ::create_room();
    set_short("field of training");
    set_long("Passing through the archway reveals that rather than an "
            +"enclosed building, the training area of Tyr is a dusty "
            +"field enclosed by walls. Presumably its best to be ready "
            +"for the unrelenting sun of Athas, even when just learning "
            +"a skill. A few people who have yet to learn this lesson "
            +"are being dragged off with bad cases of heat stroke. "
            +"<help training> will give an idea of the options here.\n");
 
  add_item(({"arch", "archway"}), "Its just a simple stone opening.\n");
  add_item(({"field", "dusty field"}), "There are some moist spots "
           +"thanks to the sweat of the students.\n");
 
  OUTSIDE
  ADD_SUN_ITEM
 
  add_exit(TYR_MERCHANT+"ironsqr8.c", "north", 0, 1);
  reset_room();
}
 
init()
{
  ::init();
  add_action("fail", "stop");
  add_action("fail", "learn");
  add_action("fail", "improve");
  add_action("fail", "skill");
}
 
int fail()
{
  NF("Nobody seems willing to help you with that.\n");
  return 0;
}
