// file name: hall15
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
   hall_long("There appears to be a room to the "
               +"northeast.");
   hall_exit("14","southwest");
   quar_exit("8","northeast");

}
