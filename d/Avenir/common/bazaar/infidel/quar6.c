// file name: quar6
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: Quarters in the Infidel Hideout
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
   quar_long("Using set_long instead.");
   set_long("This large room seems to be an armoury, with "
           +"heavy wooden racks on the west and north walls. An "
           +"open doorway leads east.\n");
   set_short("armoury");

   AI(({"rack","racks"}),"This is where weapons and armours "
           +"would be stored away when they are not needed.\n"
           +"The rack is empty.\n");   

   hall_exit("11","east");

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
        guard->add_act("hmm");
     }
}
