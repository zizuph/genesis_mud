/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"
#include <filter_funs.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR+"t01", "northeast");
  set_pull(MISTY_DIR+"c2", "north");
}

void reset_room()
{
  object goblin1;
  object goblin2; /* there are several goblins here    */

  seteuid(getuid());
  if(!present("_misty_goblin_"))
  {
    if(sizeof(FILTER_LIVE(all_inventory(TO))))
    {
      set_alarm(200.0, 0.0, "reset_room");
      return;
    }
    goblin1 = clone_object(NPC_DIR+"goblins/goblin_low");
    goblin1->arm_me();
    goblin1->move_living("xxx", this_object());
    goblin2 = clone_object(NPC_DIR+"goblins/goblin_low");
    goblin2->arm_me();
    goblin2->move_living("xxx", this_object());
    goblin2->team_join(goblin1); /* goblin2 will be the leader */
  }
}
