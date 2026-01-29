#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

#define FFF "/d/Ansalon/balifor/flotsam/room/street37"

void
reset_flotsam_room()
{
   return;
}
create_flotsam_room()
{
   set_short("Outside the gates of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"eroding dirt road","eroding road","dirt road","road"}),
      "You stand upon a wide dirt road that is slowly eroding " +
      "due to lack of maintenance.\n");
   add_item(({"gates","gate","iron gates","great iron gates"}),
      "To the north stands the great iron gates of the town " +
      "of Flotsam. At present they are open.\n");
   add_item(({"wretched port town","port town","wretched town",
            "wretched port town of Flotsam","flotsam","town"}),
      "To your north is the wretched port town of Flotsam. " +
      "Rumours have it that it is presently occupied by the Blue Dragonarmy, " +
      "for what reason you do not know.\n");
   add_item(({"fields of wheat","wheat","fields","farmed fields of wheat"}),
      "On either side of the road are the cultivated " +
      "fields of wheat that support the populace of Flotsam.\n");
   add_item(({"shadows","forest","ancient forest","evergreen forest",
            "ancient evergreen forest"}),"Past the fields to the " +
      "south, a forboding forest swallows up the road in its " +
      "shadows.\n");
   
    add_exit(FFF, "north", "@@enter_gate", 0);
   add_exit(FROOM + "roadb","south",0);
   
   
   reset_flotsam_room();
}


string
long_descr()
{
   return "You stand upon an eroding dirt road before the " +
   "gates to the wretched port town of Flotsam. To your " +
   "south the road leads away from the town, passing " +
   "through farmed fields of wheat, and in the far distance " +
   "disappearing into the shadows of an ancient evergreen " +
   "forest. " + tod_descr1() +
   "\n";
}


int
enter_gate()
{
   write("You pass through the open gates and into " +
      "the town of Flotsam.\n");
   return 0;
}
