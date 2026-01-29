/* East Battlement two of the New Vingaard, by Morrigan Dec 96 */

#include "../../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You have reached the middle of the eastern battlement of " +
      "Vingaard Keep. It continues both to the north and south, " +
      "heading towards either of the two eastern towers. ";
}

public void
create_battlement()
{
   AE(VROOM + "eb3", "north", 0);
   AE(VROOM + "eb1", "south", 0);
}
