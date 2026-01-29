/* highpass */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"
#include <filter_funs.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
    add_prop(ROOM_I_LIGHT, 0);    

    set_short("inside cave");
    set_long("This is a filthy dark cave. Fortunately you have a light " + 
             "by which you can see the walls around you.\n");

    add_exit(MISTY_DIR+"p19", "out",    0,    4);

  set_push(CAVE_DIR+"t00", "south");
}

void reset_room()
{
  object goblin1; 
  object goblin2; /* there are several goblins here    */

  seteuid(getuid());

  if (!present("_misty_goblin_"))
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