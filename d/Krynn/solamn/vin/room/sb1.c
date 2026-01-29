/* South Battlement one of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are on the south battlement of Vingaard Keep. West is a "+
   "tower, where you can go down to the lower levels, while east is "+
   "the battlement above the outer gate of Vingaard. ";
}

public void
create_battlement()
{
   AE(VROOM + "swtowerup", "west", 0);
   AE(VROOM + "sb2", "east", 0);
}
