// file name: hall1
// creator: Ilyian (September 9, 1995)
// last update:
// purpose: Hallway in the Infidel Hideout
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void
create_room()
{
   hall_long("A rickety set of wooden stairs leads up.");
   AI(({"stair","stairs","staircase"}),"The narrow wooden stairs "
           +"lead up into darkness.\n");
   hall_exit("2","west");
   AE(BAZAAR+"infidel/stair1","up",0,1);

}
