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
   set_short("Northern wing of a forsaken temple");
   set_long("@@long_descr");
   
   add_item(({"walls","grey marble walls","marble walls"}),
      "These grey marble walls were once exquisitely carved " +
      "to portray something, but the hand of time has made " +
      "it impossible to say what.\n");
   add_item(({"temple","wing","forsaken temple","chamber"}),
      "@@long_descr");
   add_item("passageway","A passageway leads out of this " +
      "chamber to the south.\n");
   
   add_exit(CROOM + "temp3","south",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in the northern grey marble walled " +
   "wing of a forsaken temple. You gather priests used " +
   "to gather here for private contemplation. A passageway " +
   "leads away to the " +
   "south.\n";
}
