// file name: hall2
// creator: Ilyian (September 9, 1995)
// last update:
// purpose: Hallway in the Infidel Hideout
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void reset_room();

object guard;
void
create_room()
{
   hall_long("The hallway divides here, with one branch leading "
               +"off to the northwest, and the other heading "
               +"southwest.");
   hall_exit("4","southwest");
   hall_exit("3","northwest");
   hall_exit("1","east");

   reset_room();
}

void
reset_room()
{
   if(!guard)
     {
        guard = clone_object(MON+"guard");
        guard->arm_me();
        guard->move(TO);
     }
}
