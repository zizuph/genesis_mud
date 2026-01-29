/* Northern battlement two of the New Vingaard, by Morrigan Dec 96 */

#include "../../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
   return "You are in the center of the northern battlement of Vingaard. "+
   "Opposite the Outer Gates, you look down into the residential areas "+
   "of Vingaard. To your east and west the northern battlement continues. ";
}

public void
create_battlement()
{

   AI(({"residential areas","areas"}),"Perhaps one day, real houses " +
      "will be constructed there. As of now, they are simply barracks.\n");

   AE(VROOM + "nb1", "west", 0);
   AE(VROOM + "nb3", "east", 0);
}
