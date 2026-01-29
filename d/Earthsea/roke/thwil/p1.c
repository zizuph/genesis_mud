#include "defs.h"
#include "/d/Earthsea/herbs/herb_sets/meadow_herbs.h"
inherit THWIL_BASE_ROOM;
inherit "/d/Earthsea/herbs/specials/hs";

#pragma strict_types

object *sheep = allocate(3);

void reset_room();

void
create_thwil_room()
{
  set_short("Paddock");
  set_long("This is a lush green paddock. In the distance "+
	   "you hear the relaxing sound of bleating sheep. "+
	   "To the south you see a town. In all other directions "+
	   "the pasture continues. \n");
  add_exit(THWIL + "p4", "north");
  add_exit(THWIL + "p6", "east");
  add_exit(THWIL + "p2", "west");
  add_exit(THWIL + "t8" , "south");

  add_prop(OBJ_I_SEARCH_TIME, 2);
  set_up_herbs(select_herb_files(MEADOW_HERBS), MEADOW_LOCATIONS, 3);
  FIELD;
  reset_room();
}

void
reset_room()
{
  int i = sizeof(sheep);
  while (i--)
    {
      if (!objectp(sheep[i]))
	{
	  sheep[i] = clone_object(THWIL + "monster/sheep");
	  sheep[i]->move(this_object(), 1);
	}
    }
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
