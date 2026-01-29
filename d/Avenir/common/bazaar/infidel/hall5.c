// file name: hall5
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
   hall_long("The passage extends west into darkness, and branches "
               +"out to the northeast and southeast.");
   hall_exit("6","west");
   hall_exit("3","northeast");
   hall_exit("4","southeast");

}
