/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"
#include <macros.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"

void reset_room(){}

void create_room()
{
  set_short("Dirty goblin hotel");
  set_long("You are in a big dirty cave under the Misty "
    + "Mountains.  It is very humid and the walls are damp with condensed "
    + "water. The whole room is full of beds. Most of them are empty but "
    + "some of them have covers on. If you have a cover then you can "
    + "sleep here overnight.\n");

  add_item(({"bed","beds"}),"These beds don't look very comfortable but "+
                "it is better than nothing if you really want to sleep.\n");
  add_item("covers","You see some covers on couple of beds but they were "+
                    "used and you don't dare sleep there.\n");

  set_pull(CAVE_DIR+"t29", "east");
}

void init()
{
  ::init();
  add_action("start_here","start");
  add_action("start_here","sleep");
}

int start_here(string arg)
{
  object ob;

  NF(CAP(query_verb())+" where?\n");
  if(arg != "here") return 0;

  ob = present("_bed_cover_for_goblin_hotel_",TP);
  if(!ob)
  {
    write("How do you want to make a bed for yourself without bed covers?\n");
    return 1;
  }

  if(TP->set_temp_start_location(CAVE_DIR + "hotel"))
  {
    ob->remove_object();
    say(QCTNAME(TP)+" puts covers on an empty bed.\n");
    write("You put covers on an empty bed. Suddenly you are confident that "+
          "you will wake up here the next time you enter the game.\n");
  }
  else write("Please try again and if you don't succeed report a bug.\n");
  return 1;
}
