// file name: hall14
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
   hall_long("The passage extends off to the north, southeast, and "
               +"northeast here.");
   hall_exit("16","north");
   hall_exit("13","southeast");
   hall_exit("15","northeast");

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
