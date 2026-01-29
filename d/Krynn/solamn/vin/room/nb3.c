/* Northern battlement three of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are on the northern battlement, just west of the "+
   "northeastern tower. The tower leads down to the ground level. ";
}

public void
create_battlement()
{
   AE(VROOM + "nb2", "west", 0);
   AE(VROOM + "netowerup", "east", 0);
}
