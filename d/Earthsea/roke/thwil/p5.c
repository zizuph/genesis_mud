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
	   "The pasture continues to the south and west.\n");
  add_item(({"cliff", "north"}), "The cliff seems unscalable.\n");

  add_exit(THWIL + "p4", "west");
  add_exit(THWIL + "p6", "south");
  
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
