/* Southwest Battlement of the New Vingaard, by Morrigan Dec 96 */

#include "../../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are on the southwest corner of the battlements of Vingaard "+
   "Keep. Here, a ladder leads down into the lower level of the tower. ";
}

public void
create_battlement()
{
   AE(VROOM + "wb1", "north", 0);
   AE(VROOM + "sb1", "east", 0);
   AE(VROOM + "swtower", "down", 0);
}
