/* Northern battlement one of the New Vingaard, by Morrigan Dec 96 */

#include "../../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are on the northern battlement, close to the northwestern "+
   "corner of the Keep. ";
}

public void
create_battlement()
{
   AE(VROOM + "nwtowerup", "west", 0);
   AE(VROOM + "nb2", "east", 0);
}
