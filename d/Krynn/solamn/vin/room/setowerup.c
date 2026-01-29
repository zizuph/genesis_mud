/* Southeastern battlement of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are on the southeastern corner of the battlements of the "+
   "Keep. A ladder leads down here, and the southern and eastern "+
   "battlements stretch out to the west and north respectively. ";
}

public void
create_battlement()
{
   AE(VROOM + "sb3", "west", 0);
   AE(VROOM + "eb1", "north", 0);
   AE(VROOM + "setower", "down", 0);
}
