// file name: hall9
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
   hall_long("The passage turns from the southeast to the north here. There "
               +"appears to be a room to the southwest.");
   quar_exit("5","southwest");
   hall_exit("10","north");
   hall_exit("8","southeast");

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
