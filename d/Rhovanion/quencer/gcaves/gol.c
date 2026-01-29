/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"
#include <filter_funs.h>
#include <stdproperties.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  set_short("By the cave lake");
  set_long("Here the tunnel ends. North of you is some quite big "+
            "cave. Unfortunately it is very dark and filled with water. "+
            "You have a feeling that there is something dangerous hidden "+
            "in it. Better turn back and run away as quick as possible.\n");

  add_item("water","The water is dark and icy cold. No way to swim in it.\n");
  add_item("cave","It looks big but you can't tell more because it is "+
                  "dark and full of water.\n");

  add_exit(CAVE_DIR + "t55", "south");
}

void reset_room()
{
  object gollum;

  seteuid(getuid());

  if(!present("gollum"))
  {
    if(sizeof(FILTER_LIVE(all_inventory(TO))))
    {
      set_alarm(200.0, 0.0, "reset_room");
      return;
    }
    gollum = clone_object(NPC_DIR+"gollum");
    gollum->add_prop(LIVE_I_SEE_DARK, 2);
    gollum->move_living("xxx", TO);
  }
}
