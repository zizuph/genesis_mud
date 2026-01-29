// file name: hall3
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
   hall_long("The hall bends here, turning from the southeast to the "
               +"southwest.");
   hall_exit("5","southwest");
   hall_exit("2","southeast");

}
