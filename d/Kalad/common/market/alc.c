/*
 *   A shop to mix and sell potions.
 *              -Rico 10.10.95
 */

inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("\n" + "Inside Ehelwin's Elixers\n\n");
   set_long("\n"+
      "You are inside Ehelwin's Elixers.\n"+
      "There is an old wooden table here.  It looks "+
      "as though Ehelwin himself might do more than "+
      "sell elixers over it.\n "+
      "Unfortunately for his regular patrons, Ehelwin "+
      "is nowhere to be seen.  He must be off looking "+
      "for some new, exotic concoctions.  Hopefully he'll "+
      "be back in a few days. "+
      "\n\n");
   
   add_item(({ "table", "wooden table", "old wooden table" }),
      "\n"+
      "This table is a mess!\n"+
      "Without Ehelwin here to find things for you, you wouldn't "+
      "be able to find a thing even with instructions! "+
      "\n\n");

   add_exit(MRKT_PATH(m25), "west");
}
