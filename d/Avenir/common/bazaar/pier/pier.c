// file name: pier.c
// creator(s): Ilyian May 1995
// last update:
// purpose: Connect bazaar to the outpost boat
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Avenir/common/common.h"

create_room()
{
set_short("Top of wooden pier");
set_long("You stand atop a short wooden pier that extends a short way "+
         "to the west, where a rickety walkway leads down to some "+
         "floats below. To the east you can see, and hear, the "+
         "beginnings of a crowded marketplace. Below you lies "+
         "black, swirling water.\n");

AI(({"pier","dock"}),"It is made from strong wool, and raised up "+
   "from the black water by long poles. This pier seems much to "+
   "high to dock a ship at. To the west, a walkway leads down "+
   "to a large float.\n");
AI(({"float"}),"The float below you seems strong, if a bit unsteady.\n");
AI(({"water","sea","ocean"}),"The black sea surrounds this island "+
   "for as far as you can see. In the distance to the west, you can "+
   "barely make out the great walls of the cavern that rise up to "+
   "staggering heights, and along the wall is a narrow, winding ledge.\n");
AI(({"marketplace","bazaar","east"}),"The bazaar to the east seems to "+
   "be densely packed with merchants, guards, slaves, and various others. "+
   "In the center you can just make out a large hill that overlooks the "+
   "entire marketplace.\n");
AI(({"ledge","wall"}),"@@my_ledge");


AE(BAZAAR+"extr/str10","east",0);
AE(BAZAAR+"pier/float","down",0);

add_prop(ROOM_I_LIGHT,1); 
IN

}

my_ledge()
{
  if (random(2)==1)
    {
     return("You can barely make out a tiny shape moving along the ledge.\n");
     }
   else 
     {
     return("The ledge winds down from a cavern at the top of the high "+
            "western wall. There does not appear to be anyone on it.\n");
      }
// I know, I know, this is a cop-out... but maybe it can be
// modified for a quest or something later.
}


go_down()
{
write("You make your way down the rickety walkway.\n");
return 0;
}

