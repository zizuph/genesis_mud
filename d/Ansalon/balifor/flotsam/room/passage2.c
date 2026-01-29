#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("A dark passageway under a deserted manor in Flotsam");
   set_long("@@long_descr");
   
   add_item(({"walls","stone walls","cold stone walls"}),"The walls " +
      "are made of big blocks of grey stone. You doubt that they have " +
      "seen the light of day for many years.\n");
   add_item("passageway","The passageway leads north and west " +
      "into shadows.\n");
   
   add_exit(FROOM + "passage4","north",0);
   add_exit(FROOM + "passage1","west",0);
   
   DARK;
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in a dark passageway in the cellar of a " +
   "deserted house in the town of Flotsam. It is uncomfortably " +
   "silent down here. Not even vermin make their home in this " +
   "evil place. " +
   "The cold stone walls of the passageway continue to " +
   "the north and west. " +
   "\n";
}
