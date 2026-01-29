#include "defs.h"
#include "/d/Earthsea/herbs/herb_sets/meadow_herbs.h"
inherit THWIL_BASE_ROOM;
inherit "/d/Earthsea/herbs/specials/hs";

#pragma strict_types

void
create_thwil_room()
{
  set_short("Paddock");
  set_long("This is a lush green paddock. In the distance "+
	   "you hear the relaxing sound of bleating sheep. "+
	   "To the north the paddock is cut off by a cliff. " +
	   "The pasture continues to the south and east. There " +
	   "is a pig pen to the west.\n");
  add_item(({"cliff", "north"}), "The cliff seems unscalable.\n");
  add_item(({"pen", "pig pen"}), "It is partitioned from the paddock " +
	   "to keep the pigs away from the sheep.\n");
  add_exit(THWIL + "p4", "east");
  add_exit(THWIL + "p2", "south");

  add_prop(OBJ_I_SEARCH_TIME, 2);
  set_up_herbs(select_herb_files(MEADOW_HERBS), MEADOW_LOCATIONS, 3);
  FIELD;
}
 
int count_sheep()
{
  object *inv;
  int i, count;

  inv = all_inventory(this_object());
  for (i = 0, count = 0; i < sizeof(inv); i++)
    {
      if (inv[i]->query_name() == "Sheep")
	{
	  count++;
	}
    }
  return count;
}

int
pig(string str)
{
  notify_fail("Enter what? The pig pen?\n");
  if (str == "pen" || str == "pig pen")
    {
      this_player()->move_living("entering the pig pen", THWIL+"pig", 1);
      return 1;
    }
  return 0;
}

void init()
{
  ::init();
  add_action(pig, "enter");
}
