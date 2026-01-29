// file name: hall16
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
   hall_long("The hall extends south into darkness, and to the north "
               +"there appears to be a very large room.");
   hall_exit("14","south");
   quar_exit("_meet","north");

}
