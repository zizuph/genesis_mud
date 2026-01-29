/* East Battlement three of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are on the eastern battlement of Vingaard Keep, a bit "+
   "south of the northeastern tower. The battlement leads south to "+
   "the southeastern tower. ";
}

public void
create_battlement()
{
   AE(VROOM + "netowerup", "north", 0);
   AE(VROOM + "eb2", "south", 0);
}
