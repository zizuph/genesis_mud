#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Within a minotaur maze");
   set_long("@@long_descr");
   
   add_item(({"walls","stone walls","great stone walls"}),
      "These great stone walls are ten feet high and riddled " +
      "with holes. The stonework makes you think that this " +
      "maze was crafted by minotaurs.\n");
   add_item(({"holes","tiny holes"}),
      "Tiny holes riddle the walls and floor, for what reason " +
      "you do not know. Looking through the holes in the " +
      "walls makes you think that these walls must be " +
      "at least five feet thick.\n");
   add_item("floor","The floor of the maze is riddled " +
      "with holes.\n");
   
   add_exit(MAZE + "b8","up",0);
   add_exit(MAZE + "d8","down",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand within the great stone walls of a " +
   "complex maze. The walls and floor are riddled with " +
   "tiny holes, and through them you can hear the sound of " +
   "the sea.\n";
}
