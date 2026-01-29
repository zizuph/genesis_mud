#include "defs.h"
inherit THWIL_BASE_ROOM;
inherit "/d/Earthsea/herbs/specials/hs";

#pragma strict_types

#define PIG "/d/Earthsea/roke/thwil/monster/pig"

object pig1;
object pig2;

void
create_thwil_room()
{
  set_short("Pig Pen");
  set_long("This is a small pig pen. It is completely fenced in " +
	   "to keep the pigs away from the sheep. At one end you " +
	   "see a trough where the pigs feed. In the distance "+
	   "you hear the relaxing sound of bleating sheep. The " +
	   "paddock is to the east.\n");
  add_item("trough", "It is filled with leftovers from dinner.\n");
  add_item("paddock", "The paddock is for sheep.\n");
  set_no_npc(1);
  reset_room();
  FIELD;
}
 
void reset_room()
{
  if (!objectp(pig1))
    {
      pig1 = clone_here(PIG);
      pig1->move(this_object());
    }
  if (!objectp(pig2))
    {
      pig2 = clone_here(PIG);
      pig2->move(this_object());
    }
  ::reset_room();
}

int
paddock(string str)
{
  notify_fail("Enter what? The paddock?\n");
  if (str == "paddock")
    {
      this_player()->move_living("entering the paddock", THWIL+"p3", 1);
      return 1;
    }
  return 0;
}

void init()
{
  ::init();
  add_action(paddock, "enter");
}
