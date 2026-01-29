// file name: hall6
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
   hall_long("The passage extends to the west and east, and to the "
               +"north and southeast appear to be rooms.");
   quar_exit("1","north");
   quar_exit("2","southeast");
   hall_exit("7","west");
   hall_exit("5","east");

}
