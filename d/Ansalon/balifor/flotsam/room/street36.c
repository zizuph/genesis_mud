#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Cobbled street in the southern part of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"street","cobblestone street"}),"A filthy " +
      "well-used cobblestone street. \n");
   add_item("clouds","Dark gloomy clouds seem to hover " +
      "permanently over the town of Flotsam.\n");
   add_item(({"town","flotsam","centre"}),"To the north " +
      "is the wretched town of Flotsam, presently occupied by " +
      "the dragonarmies of the Dark Queen.\n");
   add_item(({"gates","iron gates"}),"To your south rise " +
      "the double iron gates of the town of Flotsam. \n");
   
   add_exit(FROOM + "street35","north",0);
   add_exit(FROOM + "street37","south",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a " +
   "gloomy cobblestone street in the town of Flotsam. To your south " +
   "stands the iron gates that lead out of this wretched town. " +
   "To your north lies the crowded streets that make up the centre of " +
   "Flotsam. " + season_descr() + "\n";
}
