// file name: hall7
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
   hall_long("There appear to be rooms to the south and northwest. The "
               +"passage continues to the west and east.");
   quar_exit("3","northwest");
   quar_exit("4","south");
   hall_exit("8","west");
   hall_exit("6","east");

}
