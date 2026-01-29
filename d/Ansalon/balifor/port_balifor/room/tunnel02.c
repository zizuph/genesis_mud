#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit         BALIFOR_OUT;

create_balifor_room()
   {
   set_short("Old abandoned street in Balifor");
   set_long("@@long_descr");
   add_item(({"steppes", "Steppes"}), "You see the Steppes that shelter " +
      "the Port City of Balifor. The Steppes slope down to the street " +
      "you are on, though not quite as steep as in other places.\n");
   add_item(({"area", "ground", "street", "dust"}), "Upon closer examination " +
      "of the dusty street, you notice some fresh tracks here leading " +
      "up to the mountains.\n");
   add_search("steppes", 3, "search_steppes", 1);
   add_exit(BROOM + "tunnel01", "northwest", 0);
}

void
init()
{
   ::init();
   add_action("climb_steppes", "climb");
}

int
climb_steppes(string dir)
{
   if (dir == "up" || dir == "up steppes" || dir == "steppes") {
      write("You scramble up the slope.\n");
      say(QCTNAME(TP) + " climbs up the slope.\n");
      TP->move_living(BROOM + "slope", 0, 0);
      return 1;
   }
   NF("Climb where?\n");
   return 0;
}

mixed
search_steppes()
{
   return "As you take a closer look at the Steppes, you think you might " +
   "be able to climb up the slope here.\n";
}

string
long_descr()
{
   return "The old abandoned street ends here as it meets the Steppes. " +
   "Strangely enough, you can't find anything here worth looking at. " +
   "The dusty street leads up to the slopes of the Steppes here. " +
   "Then you suddenly realise that it might be that very reason that " +
   "caused the street to be closed to begin with. You can go back " +
   "towards the City to the northwest, and that seems to be the only " +
   "possible exit unless you feel like scaling the Steppes...\n";
}
