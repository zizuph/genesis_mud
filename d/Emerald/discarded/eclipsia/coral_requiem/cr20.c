/* Created by Lucas */
/* Modified by Kieryn */
   

#include "/d/Emerald/eclipsia/edefs.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;

object kraken;

//Prototypes
void reset_room();
int enter(string str);

create_room()
{
   ::create_room();
   set_short("Caves around Coral Requiem");
   set_long("    As you walk about the giant wreck, you wonder how " +
      "something this big could have been shattered like it is. " +
      "Most of the hull still remains intact, but the masts and " +
      "sails have been shredded into nothingness. You " +
      "notice a few skeletons tucked away in the wreckage. " +
      "Whoever was on that ship obviously had no chance for escape.\n\n");
   
   add_item(({"wreck","shipwreck","ship","wreckage"}),
      "What a horrible end for such a beautiful ship. " +
      "The hull is in two giant pieces, but other than that, " +
      "still looks the same as it did when it sailed " +
      "the open seas.\n");
   add_item(({"skeleton", "skeletons"}), "All that is left of the " +
      "crew is their mangled skeletons.\n");
   add_item("hull","The hull is split in two. You notice " +
      "a small hole however on the bottom of one piece.\n");
   add_item("hole", "The dark hole is probably large enough to enter.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr19", "northwest");
   reset_room();
}

void
reset_room()
{
   if (!kraken)
      {
      kraken = clone_object("/d/Emerald/eclipsia/npc/shekraken");
      kraken->move(this_object(), 1);
   }
   else
      return;
}

void
init()
{
   ::init();
   add_action(enter, "enter");
}

int
enter(string str)
{
   notify_fail("Enter what?\n");
   if (str != "hole")
      return 0;
   if (kraken && CAN_SEE_IN_ROOM(kraken) && CAN_SEE(kraken, this_player()))
      {
      kraken->stop_player(this_player());
      return 1;
   }
   this_player()->move_living("into the hole", CRDIR + "treasureroom");
   return 1;
}
