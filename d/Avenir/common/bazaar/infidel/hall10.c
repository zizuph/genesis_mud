// file name: hall10
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
   hall_long("The passageway extends to the south, and branches "
               +"off to the northwest and northeast.");
   hall_exit("11","northwest");
   hall_exit("12","northeast");
   hall_exit("9","south");

}
