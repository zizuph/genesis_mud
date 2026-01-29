#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/local.h"

inherit         BALIFOR_OUT;

create_balifor_room()
   {
   set_short("Old abandoned street in Balifor");
   set_long("@@long_descr");
   add_item(({"cave", "mine"}), "This looks like an entrance to an old " +
      "that is caved in. It probably collapsed during the Cataclysm. " +
      "There must be a layer of rocks hundreds of feet thick covering " +
      "the entrance.\n");
   add_item(({"rock", "rocks"}), "There are literally tons of rocks " +
      "covering the entrance to the cave.\n");
   add_cmd_item("rocks", "move", "You try to move the rocks, but quickly " +
      "give up.\n");
   add_exit(BROOM + "city05", "northwest", 0);
   add_exit(BROOM + "tunnel02", "southeast", 0);
}

string
long_descr()
{
   return "You are on an old abandoned road south of the Port City " +
   "of Balifor. The boards you climbed over to get here are to your " +
   "northwest. There doesn't seem to be much here, just an old mine " +
   "that apparently has been caved in. The road continues southeast " +
   "but there doesn't appear to be anything this way.\n";
}
