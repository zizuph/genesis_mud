/* Western battlement one of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are on the western battlement of Vingaard. To your south is "+
   "the southwestern tower of the Keep. ";
}

public void
create_battlement()
{
   AE(VROOM + "wb2", "north", 0);
   AE(VROOM + "swtowerup", "south", 0);
}
