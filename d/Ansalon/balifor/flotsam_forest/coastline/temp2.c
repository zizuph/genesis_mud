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
   set_short("Western wing of a forsaken temple");
   set_long("@@long_descr");
   
   add_item(({"western wing","wing"}),
      "You stand within the western wing of a forsaken " +
      "temple. Grey marble walls fall away to a passage out " +
      "to the west, and a passage into the center of the " +
      "temple to the east.\n");
   add_item(({"walls","marble walls","grey marble walls"}),
      "These grey marble walls were once exquisitely carved " +
      "to portray something, but the hand of time has made " +
      "it impossible to say what that was.\n");
   add_item(({"vaulted passage","western passage"}),
      "A vaulted passage leads out of the temple.\n");
   add_item("passage","Which passage did you wish to look at?\n");
   add_item("eastern passage","A passage to the east leads " +
      "into the dome-roofed center of the temple.\n");
   add_item(({"temple","forsaken temple"}),"@@long_descr");
   add_item(({"dome-roofed center of the temple","center",
            "dome-roofed center"}),
      "To the east is the dome-roofed center of this temple.\n");
   
   add_exit(CROOM + "temp1","west",0);
   add_exit(CROOM + "temp3","east",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand within the western wing of a forsaken " +
   "temple of some sort. The first thing you notice as you " +
   "step in here is the silence, silence that seems to have " +
   "been undisturbed for a long, long time. To the " +
   "west a vaulted passage leads out of the temple, while " +
   "to the east a passage opens up to the dome-roofed " +
   "center of the temple.\n";
}
