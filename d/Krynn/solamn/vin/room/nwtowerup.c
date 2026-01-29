/* Northwestern one of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "At the northwestern corner of Vingaard, you notice that this "+
   "is the only corner without a watchtower built. As you look over "+
   "the wall, you also notice a small piece of land at the bottom "+
   "that looks rather inconsequential. ";
}

public void
create_battlement()
{
   AI(({"land","piece of land","small piece of land","ledge"}), 
      "@@ledge_desc");
   AE(VROOM + "nb1", "east", 0);
   AE(VROOM + "wb3", "south", 0);
}
