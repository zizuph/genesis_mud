inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("This is the place where the two major corridors in the Mountain "
         + "intersects. Right in the center of the crossing there is a "
         + "brass star, laid in the smooth stone floor. To your southeast "
         + "there is an opening in the wall. Judging by looks of the "
         + "opening this is why they call this hall the Place of the Guards. "
         + "To your west lies the Great Hall with all it's amusements. "
         + "Continuing west beyond the Great Hall will get you to the Front "
         + "Gate. To you north lies the shabby and ill-reputed areas of the "
         + "Mountain. Many have lost their purse or worse there. Take heed, "
         + "these parts are not for weak-hearted. East of here and facing "
         + "the cold wastelands lies the East Gate. To your south the "
         + "corridor leads you towards the Army Headquarters.");  

  add_item("star","\n        ^\n        |\n      <-+->\n        |\n"
         + "        v\n");

  add_item("opening","Hmm, it sure looks official somehow. Maybe it's bec"
         + "ause of that official looking sign hung over the opening.\n");

  add_item("sign","It reads:\n\nGUARDS.\n\n");

  add_exit(ERE_DIR + "lm1c21","west",0,1);
  add_exit(ERE_DIR + "lm1c22","east",0,1);
  add_exit(ERE_DIR + "lm1c22","north",0,1);
  add_exit(ERE_DIR + "lm1c22","south",0,1);
  add_exit(ERE_DIR + "lm1c22","southeast",0,1);
}
