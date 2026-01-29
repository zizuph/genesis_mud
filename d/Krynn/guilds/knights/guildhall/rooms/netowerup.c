/* Northeastern battlement of the New Vingaard, by Morrigan Dec 96 */

#include "../../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are at the junction of the northern and eastern battlements "+
   "of Vingaard. Looking east you see the Vingaard River flowing "+
   "past rocky shores. A ladder leads down. ";
}

public void
create_battlement()
{
   AE(VROOM + "nb3", "west", 0);
   AE(VROOM + "eb3", "south", 0);
   AE(VROOM + "netower", "down", 0);
}
