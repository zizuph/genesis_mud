#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <macros.h>
#include <ss_types.h>

inherit FLOTSAM_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   
   set_short("Dark passageway under Flotsam");
   set_long("@@long_descr");
   
   add_item(({"walls","stone walls","cold stone walls"}),"The walls are " +
      "made out of big blocks of grey stone. You doubt that they have seen " +
      "the light of day for many years.\n");
   add_item("passageway","The passageway heads east and west " +
      "into shadows.\n");
   add_item(({"opening","cellar"}),"An opening to your north " +
      "leads into the cellar.\n");
   
   add_exit(FROOM + "cellar","north",0);
   add_exit(FROOM + "passage2","east",0);
   add_exit(FROOM + "passage3","west",0);
   
   DARK;
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in a dark passageway in the cellar of a deserted house " +
   "in the town of Flotsam. It is uncomfortably silent down here. Not even " +
   "vermin make their home in this evil place. The cold stone walls continue " +
   "to the east and west, while an opening to your north leads into a small " +
   "cellar.\n";
}
