/* East Battlement one of the New Vingaard, by Morrigan Dec 96 */

#include "../../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are on the eastern battlement of Vingaard Keep. " +
      "The southeastern tower is immediately to your south, while the " +
      "battlement continues north towards the northeast tower. "; 
}

public void
create_battlement()
{
   AE(VROOM + "eb2", "north", 0);
   AE(VROOM + "setowerup", "south", 0);
}
