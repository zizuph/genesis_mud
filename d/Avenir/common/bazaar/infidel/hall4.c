// file name: hall4
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
   hall_long("The passage makes a sharp turn from the "
               +"northeast to the northwest.");
   hall_exit("5","northwest");
   hall_exit("2","northeast");

}
