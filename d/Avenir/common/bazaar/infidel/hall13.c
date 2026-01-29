// file name: hall13
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
   hall_long("There is a slight bend in the passage here, from the "
              +"south to the northwest.");
   hall_exit("14","northwest");
   hall_exit("12","south");

}
