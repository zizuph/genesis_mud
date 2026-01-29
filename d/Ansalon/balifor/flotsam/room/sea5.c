#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Ansalon/common/defs.h"

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("The Bloodsea of Istar");
   set_long("You are surrounded by the waters of the " +
      "Bloodsea of Istar, so called for two reasons. " +
      "The first being the deep red colour the water turns during " +
      "a storm, the second, more sinister reason is because " +
      "of the number of people that now call the Bloodsea " +
      "their final resting place. The sea seems to be quite " +
      "turbulent, and the storm clouds overhead do not bode " +
      "well. \n");
   add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
   
   reset_flotsam_room();
}
