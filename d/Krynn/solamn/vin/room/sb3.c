/* South Battlement three of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are on the southern battlement of Vingaard Keep, and to "+
   "your east is the southeastern tower which leads down to the gound "+
   "level of the Keep. The Outer Gate is to the west. ";
}

public void
create_battlement()
{
   AI(({"gate","outer gate"}),"The mighty gates of Vingaard are beneath " + 
      "you, protecting the entrance to the Keep.\n");
   AE(VROOM + "sb2", "west", 0);
   AE(VROOM + "setowerup", "east", 0);
}
