// file name: hall11
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
   hall_long("The hallway continues to the southeast. There appear to be "
               +"rooms to the west and north.");
   quar_exit("6","west");
   quar_exit("7","north");
   hall_exit("10","southeast");

}
