#include "../stddefs.h"
#include "../desc_include/fir_forest.h"

#include "/sys/stdproperties.h"

inherit ELFTERRAIN;

#define SHORT  "Somewhere in a dark fir forest"

#define LONG \
  "You are somewhere in a dark fir forest, standing beneath majestic, aged "+\
  "trees. The ground is in almost constant shadow from the branches "+\
  "above. Only here and there can you see the occational light spot "+\
  "where the sunlight from above hits the ground.\n"

create_mapsquare(global_x, global_y, local_x, local_y)
{
  ::create_mapsquare(global_x, global_y, local_x, local_y);
  set_short(SHORT);
  set_long(WRAP(LONG));

  FIR_FOREST_STD_ITEMS;

  set_noshow_obvious(1);
}

