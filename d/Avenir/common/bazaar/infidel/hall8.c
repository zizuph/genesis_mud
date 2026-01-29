// file name: hall8
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
   hall_long("The passage makes a slight bend from the "
               +"northwest to the east here.");
   hall_exit("9","northwest");
   hall_exit("7","east");

}
